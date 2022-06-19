#include "ups.hpp"
#include "crc32.hpp"
#include <cstdint>
#include <fstream>
#include <ios>

bool UPS::patch(){
	uint64_t origSize, resSize;
	uint32_t checks[3];
	std::vector<char> buff;
	size_t i=5, offset = 0;
	if(std::memcmp(&this->_patch[0], "UPS1", 4) != 0)
		return false;
	origSize = this->readVarLength(i);
	resSize = this->readVarLength(i);
	for(; i<this->_patch.size() - 12; ++i){
		//! Check relative difference
		offset += this->readVarLength(i);
		for(; this->_patch[i] != 0; ++i){
			this->apply(offset, this->_patch[i]);
			offset++;
		}
		offset++;
	}
	for(char j=0; j<3; ++i)
		this->readBuff(checks[i], i, i+j*4);
	this->_fout.close();
	return true;
}
bool UPS::checkIntegrity(uint32_t checksum, const char* filename){
	std::ifstream fin(filename, std::ios::binary);
	size_t filesize;
	uint32_t result = 0;
	fin.seekg(std::ios::end);
	filesize = fin.tellg();
	fin.seekg(std::ios::beg);
	for(size_t i=0; i<filesize; ++i){
		char val;
		fin.read(&val, 1);
		result = CRC32::calculate(result, &val, 1);
	}
	return checksum == result;
	
}
bool UPS::load(const char* romName, const char* patchName){
	this->_fout.open("output", std::ios::binary);
	this->_patch = this->loadFile(patchName);
	this->_rom.open(romName, std::ios::binary);
	return !this->_patch.empty() && this->_rom.is_open() && this->_fout.is_open();
}
bool UPS::write(const char *filename){
	return std::rename("output", filename) == 0;
}
void UPS::readBuff(uint32_t& dest, size_t start, size_t end){
	std::vector<char> buff;
	buff.resize(end-start);
	for(size_t i=start, j=0; i<end; ++i, ++j)
		buff[j] = this->_patch[i];
	std::memcpy(&dest, &buff[0], sizeof(dest));
}
size_t UPS::readVarLength(size_t& i){
	size_t res = 0, shift = 1;
	for(; i<this->_patch.size(); ++i){
		res += (this->_patch[i] & 0x7f) * shift;
		if(this->_patch[i] & 0x80)
			break;
		shift = shift << 7;
		res += shift;
	}
	return res;
}
void UPS::apply(size_t offset, char byte){
	char val;
	this->_rom.seekg(offset);
	this->_rom.read(&val, 1);
	this->_fout.seekp(offset);
	val ^= byte;
	this->_fout.write(&val, 1);
}