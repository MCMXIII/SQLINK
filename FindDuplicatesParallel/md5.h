#include <stdio.h>
#ifndef MD5_H
#define MD5_H

	void generateKey(FILE* f, unsigned char* out);
	unsigned long hash(void* f);

#endif