// FLVview.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
// platform def
typedef unsigned char  u8_t;
typedef unsigned short u16_t;
typedef unsigned int  u32_t;

u8_t io_r8(FILE *fb){
	return (u8_t)fgetc(fb);
}

u16_t io_r16(FILE *fb){
	return (u16_t)(io_r8(fb) << 8 | io_r8(fb));
}

u32_t io_r32(FILE *fb){
	return (u32_t)(io_r16(fb) << 16 | io_r16(fb));
}

bool probe(FILE *fb){
	if (io_r8(fb) == 'F' &&
		io_r8(fb) == 'L' &&
		io_r8(fb) == 'V' &&
		io_r8(fb) < 5 &&
		io_r8(fb) != 0 &&
		io_r32(fb) < 8)
		return true;
}


int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("usage......\n");
		exit(1);
	}

	FILE *input = fopen(argv[1], "wb");
	if (!input)
		printf("open file failure\n");
	if (!probe(input))
		printf("probe file failure, maybe not FLV format\n");
	
	return 0;
}

