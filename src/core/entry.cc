//
//  ruvi base
//

// includes
#include "core/interfaces/interfaces.hh"
#include "hooks/hooks.hh"
#include "menu/menu.hh"
#include "sdk/input/input.hh"
#include "sdk/netvars/netvars.hh"
#include "sdk/render/render.hh"
#include <thread>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <winternl.h>
#endif

std::thread main_thread;

#ifndef _WIN32
// initialize all our stuff here
void constructor() {
  try {
    
  while (
      !dlopen("./bin/linux64/serverbrowser_client.so", RTLD_NOLOAD | RTLD_NOW))
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

  interfaces::on_entry_point();
  netvars::on_entry_point();
  draw::on_entry_point();
  input::on_entry_point();
  hooks::on_entry_point();
  menu::on_entry_point();
  } catch (...) {

    std::throw_with_nested(
        std::runtime_error("error handler - constructor - entry"));
  }
}

// entry point
int __attribute__((constructor)) startup() {

  // create a new thread and attach the library
  main_thread = std::thread{constructor};

  return 0;
}

#endif

bool is_mod_present(const std::wstring_view search_name)
{
	const auto peb = reinterpret_cast<PPEB>(__readfsdword(0x30));

	if (!peb)
		return false; // should never happen though

	auto ldr_mod = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(peb->Ldr->InMemoryOrderModuleList.Flink);
    for(;ldr_mod->Reserved2[0]; ldr_mod = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(reinterpret_cast<PLIST_ENTRY32>(ldr_mod)->Flink))
    {
		const auto mod_name = std::wstring_view{ ldr_mod->FullDllName.Buffer };
        // lets hope nothing unicode in here
		const auto it = std::search(mod_name.begin(), mod_name.end(), search_name.begin(), search_name.end(),
			[](const auto c1, const auto c2) -> bool { return std::tolower(c1) == std::tolower(c2); });

		if (it != mod_name.end())
			return true;
    }

	return false;
}

void __stdcall init_thread(uintptr_t)
{
	
    while(!is_mod_present( L"serverbrowser.dll" ))
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	
	interfaces::on_entry_point();
	netvars::on_entry_point();
	draw::on_entry_point();
	input::on_entry_point();
	hooks::on_entry_point();
	menu::on_entry_point();
}

BOOL WINAPI DllMain(HINSTANCE instance, const DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		CreateThread(nullptr, 0, reinterpret_cast< LPTHREAD_START_ROUTINE >( init_thread ), instance, 0, nullptr);
	}

	return TRUE;
}
