#pragma once

#include <stdint.h>
#include <iostream>
#include <stdio.h>

struct crc32q {

	static unsigned int check(void *buf, size_t l)
	{
		size_t i, j;
		uint32_t crc, msb;
		const uint8_t* u = static_cast<const uint8_t*>(buf);
		crc = 0x00000000;
		for (i = 0; i < l; i++) {
			crc ^= (((uint32_t)u[i]) << 24);
			for (j = 0; j < 8; j++) {
				msb = crc >> 31;
				crc <<= 1;
				crc ^= (0 - msb) & 0x814141AB;
			}
		}
		return crc;
	}

};

/*
	unsigned char buf[9] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};
	//for (int s = 0; s < 32; s++) printf("crc32 of struct Data is: %u\n", Crc32(buf, 1, s));

	printf("0x%x", crc32q::check(buf, 9));
*/
