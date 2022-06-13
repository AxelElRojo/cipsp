#include "patcher.hpp"
#include "util.hpp"
bool Patcher::load(const char* romName, const char* patchName){
	this->rom = this->loadFile(romName);
	this->ips = this->loadFile(patchName);
	return !(this->rom.empty() || this->ips.empty());
}
bool Patcher::write(const char* filename){
	std::ofstream fout(filename, std::ios::binary);
	fout.write(&this->rom[0], this->rom.size());
	return fout.good();
}
bool Patcher::patch(){
	char szOffset[OFFSET_SIZE], szSize[SIZE_SIZE];
	size_t offset, size;
	if(std::memcmp(&(this->ips[0]), "PATCH", 5) != 0)
		return false;
	for(size_t i=5; std::memcmp(&this->ips[i], "EOF", OFFSET_SIZE) != 0; i += size){
		std::memcpy(szOffset, &this->ips[i], OFFSET_SIZE);
		i += OFFSET_SIZE;
		std::memcpy(szSize, &this->ips[i], SIZE_SIZE);
		i += SIZE_SIZE;
		offset = BYTE3_UINT(szOffset);
		size = BYTE2_UINT(szSize);
		if(offset > this->rom.size())
			return false;
		if(size == 0){
			std::memcpy(szSize, &this->ips[i], SIZE_SIZE);
			i += SIZE_SIZE;
			size = BYTE2_UINT(szSize);
			this->rle(offset, size, this->ips[i]);
			size = 1;
		}else
			this->reg(offset, size, i);
	}
	return true;
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
void Patcher::reg(size_t offset, size_t size, size_t index){
	size_t end = offset + size;
	for(size_t i=offset; i<end; ++i)
		this->rom[i] = this->ips[index++];
}
void Patcher::rle(size_t offset, size_t size, char byte){
	size_t end = offset + size;
	for(size_t i=offset; i<end; ++i)
		this->rom[i] = byte;
}