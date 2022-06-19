#include "patcher.hpp"
bool Patcher::load(const char* romName, const char* patchName){
	this->_rom = this->loadFile(romName);
	this->_patch = this->loadFile(patchName);
	return !(this->_rom.empty() || this->_patch.empty());
}
bool Patcher::write(const char* filename){
	std::ofstream fout(filename, std::ios::binary);
	fout.write(&this->_rom[0], this->_rom.size());
	return fout.good();
}
std::vector<char> Patcher::loadFile(const char* filename){
	std::ifstream fin(filename, std::ios::binary);
	std::vector<char> output;
	if(!fin.is_open())
		return output;
	size_t size;
	fin.seekg(0, std::ios::end);
	size = fin.tellg();
	fin.seekg(0, std::ios::beg);
	output.resize(size);
	fin.read(&output[0], size);
	return output;
}