#include <iostream>
#include "patcher.hpp"
#include "util.hpp"
int main(int argc, char** argv){
	Patcher patcher;
	if(argc < 4){
		std::printf("Proper usage: %s rom patch outfile\n", argv[0]);
		errorAndExit(RET_ERR_ARG, "Not enough arguments");
	}
	if(!patcher.load(argv[1], argv[2]))
		errorAndExit(RET_ERR_LOAD, "Can't load files");
	if(!patcher.patch())
		errorAndExit(RET_ERR_PATCH, "Malformed patch");
	if(!patcher.write(argv[3]))
		errorAndExit(RET_ERR_WRITE, "Can't write file");
}