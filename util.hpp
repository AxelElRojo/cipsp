#ifndef UTIL
#define UTIL
#include <iostream>
#define RET_ERR_ARG 1
#define RET_ERR_PATCH 2
#define RET_ERR_LOAD 3
#define RET_ERR_WRITE 4
#define BYTE3_UINT(bp) \
	(((unsigned long)(bp)[0] << 16) & 0xFF0000) | \
	(((unsigned long)(bp)[1] << 8) & 0x00FF00) | \
	((unsigned long)(bp)[2] & 0x0000FF)
#define BYTE2_UINT(bp) (((unsigned int)(bp)[0] << 8) & 0xFF00) | ((unsigned int)(bp)[1] & 0x00FF)
void errorAndExit(int ret, const char* message);
#endif