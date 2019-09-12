#include <openssl/md5.h>
#include <unistd.h>
#include <string.h>
#include "md5.h"

void generateKey(FILE* f, unsigned char* out)
{
	MD5_CTX c;
	char buf[512];
	ssize_t bytes;
	MD5_Init(&c);
	bytes=read(fileno(f), buf, 512);
	while(bytes > 0)
	{
		MD5_Update(&c, buf, bytes);
		bytes=read(fileno(f), buf, 512);
	}
	MD5_Final(out, &c);
	out[MD5_DIGEST_LENGTH] = '\0';
	return;
}

unsigned long hash(void* key)
{
	int n = 0;
	unsigned long hashValue = 0;
	for(n=0; n<strlen((unsigned char*)key); n++)
	{
		hashValue*=256;
		hashValue+=((unsigned char*)key)[n];
	}
	return(hashValue);        
}