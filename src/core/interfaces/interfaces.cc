//
//  ruvi base
//

// includes
#include "interfaces.hh"
#include "sdk/memory/memory.hh"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <winternl.h>
#endif

void interfaces::on_entry_point() {

  // initialize exposed interfaces
  csgo::vgui_surface = interfaces::get_interface<i_surface>(
      "vguimatsurface_client.so->VGUI_Surface0");
  csgo::vgui_panel =
      interfaces::get_interface<i_panel>("vgui2_client.so->VGUI_Panel0");
  csgo::engine_vgui = interfaces::get_interface<i_engine_vgui>(
      "engine_client.so->VEngineVGui0");
  csgo::engine_client = interfaces::get_interface<i_engine_client>(
      "engine_client.so->VEngineClient0");
  csgo::input_system = interfaces::get_interface<i_input_system>(
      "inputsystem_client.so->InputSystemVersion0");
  csgo::input_internal = interfaces::get_interface<i_input_internal>(
      "vgui2_client.so->VGUI_InputInternal0");
  csgo::debug_overlay = interfaces::get_interface<iv_debug_overlay>(
      "engine_client.so->VDebugOverlay0");
  csgo::base_client = interfaces::get_interface<i_base_client_dll>(
      "client_panorama_client.so->VClient0");
  csgo::entity_list = interfaces::get_interface<i_client_entity_list>(
      "client_panorama_client.so->VClientEntityList0");
  csgo::cvar = interfaces::get_interface<i_cvar>(
      "materialsystem_client.so->VEngineCvar0");
  csgo::material_system = interfaces::get_interface<i_material_system>(
      "materialsystem_client.so->VMaterialSystem0");

#ifndef _WIN32
  // vfunc addresses
  std::uintptr_t hud_process_input_vfunc = reinterpret_cast<std::uintptr_t>(
      memory::get_vtable(csgo::base_client)[10]);
  std::uintptr_t get_local_player_vfunc = reinterpret_cast<std::uintptr_t>(
      memory::get_vtable(csgo::engine_client)[12]);
  std::uintptr_t hud_update_vfunc = reinterpret_cast<std::uintptr_t>(
      memory::get_vtable(csgo::base_client)[11]);

  // pointers (addresses)
  i_client_mode *(*client_mode_ptr)() =
      reinterpret_cast<i_client_mode *(*)(void)>(
          memory::get_address(hud_process_input_vfunc + 11, 1, 5));
  c_base_client_state *(*client_state_ptr)(int) =
      reinterpret_cast<c_base_client_state *(*)(int)>(
          memory::get_address(get_local_player_vfunc + 9, 1, 5));

  // initialize non exposed interfaces
  csgo::client_mode = client_mode_ptr();
  csgo::client_state = client_state_ptr(-1);
  csgo::global_vars = *reinterpret_cast<c_global_vars **>(
      memory::get_address(hud_update_vfunc + 13, 3, 7));
#else

  csgo::client_mode = **reinterpret_cast<i_client_mode***>(uintptr_t(memory::get_vtable(csgo::base_client)[10]) + 5);
  csgo::client_state = *reinterpret_cast<c_base_client_state * *>(*reinterpret_cast<void**>(
	  reinterpret_cast<uintptr_t>(memory::get_vtable(csgo::engine_client)[20]) + 1u));
  csgo::global_vars = **reinterpret_cast<c_global_vars ***>(uintptr_t(memory::get_vtable(csgo::base_client)[0]) + 0x1B);

#endif
}

#ifdef _WIN32

struct game_interface_node
{
	void* (*get_addr)();
	const char* name;
	game_interface_node* next_node;
};

inline uintptr_t jump_target(const uintptr_t jmp_addr)
{
	const auto jmp_offset = *reinterpret_cast<uintptr_t*>(jmp_addr + 1);
	return (jmp_addr + jmp_offset + 4);
}

uintptr_t find_ci_export(const uintptr_t mod_base)
{
	const auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(mod_base);
	const auto nt_header = reinterpret_cast<PIMAGE_NT_HEADERS32>(mod_base + dos_header->e_lfanew);

	const auto export_dir = reinterpret_cast<PIMAGE_EXPORT_DIRECTORY>(mod_base + nt_header->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	const auto name_list = reinterpret_cast<uint32_t*>(mod_base + export_dir->AddressOfNames);
	const auto ordinal_list = reinterpret_cast<uint16_t*>(mod_base + export_dir->AddressOfNameOrdinals);
	const auto function_list = reinterpret_cast<uint32_t*>(mod_base + export_dir->AddressOfFunctions);

    for(auto i = 0u; i < export_dir->NumberOfNames; ++i)
    {
		const auto name = std::string_view{ reinterpret_cast<const char*>(mod_base + name_list[i]) };
		if (name.compare("CreateInterface") != 0)
			continue;

		const auto func_off = function_list[ordinal_list[i]];
		return mod_base + func_off;
    }

	return 0u;
}

uintptr_t interfaces::get_interface_impl(const std::string& interface_location)
{
	const auto int_name_loc = interface_location.find("->");
	const auto int_name = std::string_view{ interface_location }.substr(int_name_loc+2);

	const auto peb = reinterpret_cast<PPEB>(__readfsdword(0x30));

	if (!peb)
		return false; // should never happen though

	auto ldr_mod = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(peb->Ldr->InMemoryOrderModuleList.Flink);
	for (; ldr_mod->Reserved2[0]; ldr_mod = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(reinterpret_cast<PLIST_ENTRY32>(ldr_mod)->Flink))
	{
		//Check for crashhandler since that crashes
		if (std::wstring_view{ldr_mod->FullDllName.Buffer}.find(L"crashhandler") != std::string::npos)
			continue;

		auto p = find_ci_export(reinterpret_cast<uintptr_t>(ldr_mod->Reserved2[0]));
		if (!p)
			continue;

		while (!(*reinterpret_cast<uint8_t*>(p) == 0xE9))
			++p;

		p = jump_target(p);

		while (!(*reinterpret_cast<uint16_t*>(p) == 0x358B))
			++p;

        // TODO: sometimes there are multiple interfaces with the same name, could be a problem with gameevents for example
		auto int_node = **reinterpret_cast<game_interface_node***>(p + 2);
        for(;int_node;int_node = int_node->next_node)
        {
			if (std::string_view{ int_node->name }.substr(0, int_name.length()) == int_name)
				return reinterpret_cast<uintptr_t>(int_node->get_addr());
        }
	}

	return 0u;
}

#endif
