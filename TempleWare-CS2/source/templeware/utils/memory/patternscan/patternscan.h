#pragma once
#include <cstdint>
#include <vector>
#include <string>

namespace M {
	template <typename T = std::uint8_t>
	T* abs(T* relative_address, int pre_offset = 0x0, int post_offset = 0x0)
	{
		relative_address += pre_offset;
		relative_address += sizeof(std::int32_t) + *reinterpret_cast<std::int32_t*>(relative_address);
		relative_address += post_offset;
		return relative_address;
	}
	std::uint8_t* FindPattern(const char* module_name, const std::string& byte_sequence);

	uintptr_t patternScan(const std::string& module, const std::string& pattern);
}