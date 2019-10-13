//
//  ruvi base
//

// includes
#include "memory.hh"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <string>
#include <string_view>
#include <windows.h>
#include <winternl.h>
#endif

struct dlinfo_t {

  std::size_t size = 0;
  std::uintptr_t address = 0;
#ifndef _WIN32
  const char *library = nullptr;
#else
    struct str_holder
    {
        str_holder(char* str) : _str(str) {}

		operator const char*() const { return _str.c_str(); }

		std::string_view str() const { return _str; }

    protected:
		std::string _str = nullptr;
    };
	str_holder library;
#endif
};

std::vector<dlinfo_t> libraries;

inline bool compare(const unsigned char *data, const unsigned char *mask,
                    const char *mask_2) {

  for (; *mask_2; ++mask_2, ++data, ++mask) {

    if (*mask_2 == 'x' && *data != *mask)
      return false;
  }

  return (*mask_2) == 0;
}

#ifndef _WIN32
bool get_library_info(const char *library, std::uintptr_t *address,
                      std::size_t *size) {

  if (libraries.size() == 0) {

    dl_iterate_phdr(
        [](struct dl_phdr_info *info, std::size_t, void *) {
          dlinfo_t library_info = {};
          library_info.library = info->dlpi_name;
          library_info.address = info->dlpi_addr + info->dlpi_phdr[0].p_vaddr;
          library_info.size = info->dlpi_phdr[0].p_memsz;
          libraries.push_back(library_info);

          return 0;
        },
        nullptr

    );
  }

  for (const dlinfo_t &current : libraries) {

    if (!strcasestr(current.library, library))
      continue;

    if (address)
      *address = current.address;

    if (size)
      *size = current.size;

    return true;
  }

  return false;
}
#else

bool get_library_info(const char* library, std::uintptr_t* address,
	std::size_t* size) {

    if(libraries.empty(  ))
    {
		const auto peb = reinterpret_cast<PPEB>(__readfsdword(0x30));

		if (!peb)
			return false; // should never happen though

		auto ldr_mod = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(peb->Ldr->InMemoryOrderModuleList.Flink);
		for (; ldr_mod->Reserved2[0]; ldr_mod = reinterpret_cast<PLDR_DATA_TABLE_ENTRY>(reinterpret_cast<PLIST_ENTRY32>(ldr_mod)->Flink))
		{
		    const auto mod_name = std::wstring_view{ ldr_mod->FullDllName.Buffer };
			const auto name_buf = reinterpret_cast<char*>(_alloca(mod_name.size()+1));

            if(!WideCharToMultiByte(CP_ACP, 0, mod_name.data(  ), mod_name.size(  ),
				name_buf, mod_name.size(  ), nullptr, nullptr))
				continue;

			name_buf[mod_name.size()] = '\0';
			const auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(ldr_mod->Reserved2[0]);
			const auto nt_header = reinterpret_cast<PIMAGE_NT_HEADERS32>(reinterpret_cast<uintptr_t>(ldr_mod->Reserved2[0]) + dos_header->e_lfanew);

			libraries.emplace_back(dlinfo_t{ nt_header->OptionalHeader.SizeOfImage, reinterpret_cast<uintptr_t>(ldr_mod->Reserved2[0]), name_buf });
		}
    }

    // so this runs under the assumption that <linux_mod_name> = <windows_mod_name>_client.so
    // and yes im stupid...
	auto name_view = std::string_view{ library };
	name_view = name_view.substr(0, name_view.length() - 10u);
	for (const dlinfo_t& current : libraries) {

		const auto cur_name = current.library.str();
		if (cur_name.length() < name_view.length())
			continue;

		if (cur_name.substr(0, name_view.length(  )) != name_view)
			continue;

		if (address)
			*address = current.address;

		if (size)
			*size = current.size;

		return true;
	}

	return false;
}

#endif

std::uint8_t *memory::find_pattern(const char *module, const char *signature) {

  static auto pattern_to_byte = [&](const char *pattern) {
    std::vector<int> bytes = {};
    char *start = const_cast<char *>(pattern);
    char *end = const_cast<char *>(pattern) + strlen(pattern);

    for (char *current_position = start; current_position < end;
         ++current_position) {

      if (*current_position == '?') {
        ++current_position;

        if (*current_position == '?')
          ++current_position;

        bytes.push_back(-1);
      }

      else
        bytes.push_back(strtoul(current_position, &current_position, 16));
    }

    return bytes;
  };

  std::uintptr_t module_ptr = 0;
  std::size_t size_of_image = 0;

  get_library_info(module, &module_ptr, &size_of_image);

  std::vector<int> pattern_bytes = pattern_to_byte(signature);
  std::uint8_t *scan_bytes = reinterpret_cast<std::uint8_t *>(module_ptr);

  std::size_t pattern_size = pattern_bytes.size();
  int *pattern_data = pattern_bytes.data();

  for (std::size_t i = 0; i < size_of_image - pattern_size; ++i) {

    bool found = true;

    for (std::size_t j = 0; j < pattern_size; ++j) {

      if (scan_bytes[i + j] != pattern_data[j] && pattern_data[j] != -1) {
        found = false;
        break;
      }
    }

    if (found)
      return &scan_bytes[i];
  }

  return {};
}
