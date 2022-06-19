#include <cstring>
#include <iostream>
#include "util.hpp"
#include "ips.hpp"
#include "ups.hpp"
Patcher* create(const char* type);
int main(int argc, char** argv){
	Patcher* patcher = nullptr;
	if(argc == 2 && std::strcmp(argv[1], "--opts") == 0){
		std::cout << "--ups\n--ips\n";
		return 0;
	}else if(argc < 5){
		std::printf("Proper usage: %s type rom patch outfile\n", argv[0]);
		std::printf("Example: %s --ips emerald.gba kaizo.ips kaizo.gba\n", argv[0]);
		errorAndExit(RET_ERR_ARG, "Not enough arguments");
	}else{
		patcher = create(argv[1]);
		if(patcher){
			if(!patcher->load(argv[2], argv[3]))
				errorAndExit(RET_ERR_LOAD, "Can't load files");
			if(!patcher->patch())
				errorAndExit(RET_ERR_PATCH, "Malformed patch");
			if(!patcher->write(argv[4]))
				errorAndExit(RET_ERR_WRITE, "Can't write file");
		}else
			errorAndExit(RET_ERR_ALLOC, "Can't allocate memory");
	}
}
Patcher* create(const char* type){
	if(std::strcmp("--ips", type) == 0)
		return new IPS;
	else if(std::strcmp("--ups", type) == 0)
		return new UPS;
	else
		return nullptr;
}