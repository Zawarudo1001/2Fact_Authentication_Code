#pragma once

#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>
#endif
#include <chrono>
#include "md5c.h"
#include <thread>
#include <process.h>
#include <stdio.h>

using namespace std;
using namespace chrono;


struct entropy {
	thread::id id;
	unsigned int pid;
	long long nsectime;
};

/*
Функция, вычисляющая псевдо-случайную величину тактовой частоты процессора. При этом, используется программная возможность получения значения опорной тактовой частоты
*/


/*
unsigned long long readTSC() {
	// _mm_lfence();  // optionally wait for earlier insns to retire before reading the clock
	return __rdtsc();
	// _mm_lfence();  // optionally block later instructions until rdtsc retires
};
*/


auto thisThreadId() {
	thread::id this_id = this_thread::get_id();
	return this_id;
};

unsigned int pid() {
	unsigned int temp;
#ifdef POSIX
	temp = getpid();
#else
	temp = _getpid();
#endif 
	return temp;
};


long long getCurTimeNSC() {
	auto p1 = std::chrono::high_resolution_clock::now();
	return duration_cast<std::chrono::nanoseconds>(p1.time_since_epoch()).count();
}


/*
int main(){

	for (int k = 0; k < 256; k++) {
		entropy temp{ thisThreadId(), pid(), getCurTimeNSC()};

		const char *msg = (const char*)&temp;
		size_t len;
		int i;
		uint8_t result[16];

		len = sizeof(entropy);

		md5((uint8_t*)msg, len, result);

		for (i = 0; i < 16; i++)
			printf("%x", result[i]);
		printf("\n");
	}
	return 0;
}

*/
