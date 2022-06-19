#ifndef IPS_HPP
#define IPS_HPP
#include <iostream>
#include <vector>
#include <cstring>
#include "patcher.hpp"
#include "util.hpp"
class IPS : public Patcher{
	static constexpr short OFFSET_SIZE = 3, SIZE_SIZE = 2;
public:
	bool patch();
private:
	void reg(size_t offset, size_t size, size_t index);
	void rle(size_t offset, size_t size, char byte);
};
#endif