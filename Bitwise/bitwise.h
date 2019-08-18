#ifndef BITWISE_H
#define BITWISE_H

int invert(unsigned char x, unsigned char y);
int rotate(unsigned char x, int rotations);
int setbits(unsigned char x, int p, int n, unsigned char y);
int setbits2(unsigned int w, int i, int j, int value);
char* compress(char* s);
char* compress2(char* s);

#endif
