#ifndef UPS_HPP
#define UPS_HPP
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdint>
#include "patcher.hpp"
#include "util.hpp"
#include "crc32.hpp"
class UPS : public Patcher{
	std::ifstream _rom;
	std::ofstream _fout;
public:
	bool patch();
	bool load(const char* romName, const char* patchName);
	bool write(const char *filename);
private:
	std::vector<char> loadFile(const char* filename);
	void readBuff(uint32_t& dest, size_t start, size_t end);
	size_t readVarLength(size_t& i);
	bool checkIntegrity(uint32_t checksum, const char* filename);
	void apply(size_t offset, char byte);
};
#endif