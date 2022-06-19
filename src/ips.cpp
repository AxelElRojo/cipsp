#include "ips.hpp"
#include "util.hpp"
bool IPS::patch(){
	char szOffset[OFFSET_SIZE], szSize[SIZE_SIZE];
	size_t offset, size;
	if(std::memcmp(&(this->_patch[0]), "PATCH", 5) != 0)
		return false;
	for(size_t i=5; std::memcmp(&this->_patch[i], "EOF", OFFSET_SIZE) != 0; i += size){
		std::memcpy(szOffset, &this->_patch[i], OFFSET_SIZE);
		i += OFFSET_SIZE;
		std::memcpy(szSize, &this->_patch[i], SIZE_SIZE);
		i += SIZE_SIZE;
		offset = BYTE3_UINT(szOffset);
		size = BYTE2_UINT(szSize);
		if(offset > this->_rom.size())
			return false;
		if(size == 0){
			std::memcpy(szSize, &this->_patch[i], SIZE_SIZE);
			i += SIZE_SIZE;
			size = BYTE2_UINT(szSize);
			this->rle(offset, size, this->_patch[i]);
			size = 1;
		}else
			this->reg(offset, size, i);
	}
	return true;
}
void IPS::reg(size_t offset, size_t size, size_t index){
	size_t end = offset + size;
	for(size_t i=offset; i<end; ++i)
		this->_rom[i] = this->_patch[index++];
}
void IPS::rle(size_t offset, size_t size, char byte){
	size_t end = offset + size;
	for(size_t i=offset; i<end; ++i)
		this->_rom[i] = byte;
}