#include "util.hpp"
void errorAndExit(int ret, const char* message){
	std::cout << "ERROR: " << message << "\n.";
	std::exit(ret);
}