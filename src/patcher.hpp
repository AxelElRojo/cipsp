#ifndef PATCHER
#define PATCHER
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "util.hpp"
class Patcher{
	std::vector<char> rom, ips;
	static constexpr short OFFSET_SIZE = 3, SIZE_SIZE = 2;
public:
	bool load(const char* romName, const char* patchName);
	bool write(const char* filename);
	bool patch();
private:
	std::vector<char> loadFile(const char* filename);
	void reg(size_t offset, size_t size, size_t index);
	void rle(size_t offset, size_t size, char byte);
};
#endif