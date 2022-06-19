#ifndef CRC_HPP
#define CRC_HPP
#include <cstdint>
#include <cstddef>

class CRC32{
	static uint32_t table[256];
public:
	static void generate_table();
	static uint32_t calculate(uint32_t initial, const void* buf, size_t len);
};
#endif