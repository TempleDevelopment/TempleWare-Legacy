#include "patternscan.h"

#include "../../module/module.h"

#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <span>
#include <sstream>

#include <Psapi.h>
#include <algorithm>
#include <string_view>
#include <cstdint>
#include <functional>
#include <string>
std::vector<std::pair<uint8_t, bool>> PatternToBytes(const std::string& pattern) {
    std::vector<std::pair<uint8_t, bool>> patternBytes;
    const char* start = pattern.c_str();
    const char* end = start + pattern.size();

    for (const char* current = start; current < end; ++current) {
        if (*current == ' ') continue;
        if (*current == '?') {
            patternBytes.emplace_back(0, false);
            if (*(current + 1) == '?') ++current;
        }
        else {
            patternBytes.emplace_back(strtoul(current, nullptr, 16), true);
            if (*(current + 1) != ' ') ++current;
        }
    }

    return patternBytes;
}

uintptr_t M::patternScan(const std::string& module, const std::string& pattern) {
    uintptr_t baseAddress = modules.getModule(module);
    HMODULE hModule = reinterpret_cast<HMODULE>(baseAddress);

    if (!hModule) return 0;

    MODULEINFO moduleInfo;
    GetModuleInformation(GetCurrentProcess(), hModule, &moduleInfo, sizeof(MODULEINFO));

    size_t moduleSize = moduleInfo.SizeOfImage;

    std::vector<std::pair<uint8_t, bool>> patternBytes = PatternToBytes(pattern);
    size_t patternLength = patternBytes.size();

    for (size_t i = 0; i < moduleSize - patternLength; ++i) {
        bool found = true;
        for (size_t j = 0; j < patternLength; ++j) {
            if (patternBytes[j].second && patternBytes[j].first != *reinterpret_cast<uint8_t*>(baseAddress + i + j)) {
                found = false;
                break;
            }
        }
        if (found) {
            return baseAddress + i;
        }
    }

    return 0;
}


std::uint8_t* M::FindPattern(const char* module_name, const std::string& byte_sequence)
{
	// retrieve the handle to the specified module
	const HMODULE module = GetModuleHandleA(module_name);
	if (module == nullptr)
		return nullptr;

	// retrieve the DOS header of the module
	const auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
	if (dos_header->e_magic != IMAGE_DOS_SIGNATURE)
		return nullptr;

	// retrieve the NT headers of the module
	const auto nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(module) + dos_header->e_lfanew);
	if (nt_headers->Signature != IMAGE_NT_SIGNATURE)
		return nullptr;

	// get the size and base address of the code section
	DWORD m_size = nt_headers->OptionalHeader.SizeOfCode;
	std::uint8_t* m_base = reinterpret_cast<std::uint8_t*>(module) + nt_headers->OptionalHeader.BaseOfCode;

	using SeqByte_t = std::pair< std::uint8_t, bool >;

	std::string str{ };
	std::vector< std::pair< std::uint8_t, bool > > byte_sequence_vec{ };
	std::stringstream stream(byte_sequence);
	// parse the byte sequence string into a vector of byte sequence elements
	while (stream >> str)
	{
		// wildcard byte
		if (str[0u] == '?')
		{
			byte_sequence_vec.emplace_back(0u, true);
			continue;
		}

		// invalid hex digit, skip this byte
		if (!std::isxdigit(str[0u]) || !std::isxdigit(str[1u]))
			continue;

		byte_sequence_vec.emplace_back(static_cast<std::uint8_t>(std::strtoul(str.data(), nullptr, 16)), false);
	}

	// end pointer of the code section
	const auto end = reinterpret_cast<std::uint8_t*>(m_base + m_size);

	// search for the byte sequence within the code section
	const auto ret = std::search(reinterpret_cast<std::uint8_t*>(m_base), end, byte_sequence_vec.begin(), byte_sequence_vec.end(),
		[](const std::uint8_t byte, const std::pair< std::uint8_t, bool >& seq_byte)
		{
			return std::get< bool >(seq_byte) || byte == std::get< std::uint8_t >(seq_byte);
		});

	// byte sequence found, return the pointer
	if (ret)
		return ret;
#ifdef _DEBUG

	// failed to find byte sequence, log error and return
	std::cout<< "failed to find pattern:" << byte_sequence.c_str() << " | inside: " << module_name << std::endl;

#endif
	return nullptr;
}