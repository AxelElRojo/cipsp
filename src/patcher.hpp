#ifndef PATCHER_HPP
#define PATCHER_HPP
#include <vector>
#include <fstream>
class Patcher{
protected:
	std::vector<char> _rom, _patch;
	std::vector<char> loadFile(const char* filename);
public:
	virtual bool load(const char* romName, const char* patchName);
	virtual bool write(const char* filename);
	virtual bool patch() = 0;
};
#endif