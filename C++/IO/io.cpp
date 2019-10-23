#include "asciiIO_t.h"
#include "binIO_t.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	asciiIO_t aIO("text.txt", "w");
	aIO << 'M' << 'H' << 'F' << 'C' << 1913;
	aIO.fileClose();
	aIO.fileOpen("text.txt", "r+");
	asciiIO_t aIO2("text2.txt", "w+");
	binIO_t bIO("binaryfile", "w+");
	aIO2 << 19.13;
	bIO << "NBMH",4;
	char mhfc[4];
	aIO.setPosition(0);
	aIO2.setPosition(0);
	try
	{
		for(int i = 0; i < 4; i++)
		{
			aIO >> mhfc[i];
		}
	}
	catch(string ex)
	{
		cout << ex << endl;
	}
	int number;
	float incomplete;
	try
	{
		aIO >> number;
	}
	catch(string ex)
	{
		cout << ex << endl;
	}
	try
	{
		aIO2 >> incomplete;
	}
	catch(string ex)
	{
		cout << ex << endl;
	}
	bIO.setPosition(0);
	char nb[4];
	try
	{
		bIO >> nb,4;
	}
	catch(string ex)
	{
		cout << ex << endl;
	}
	cout << mhfc << ' ' << number << ' ' << nb << endl;
	cout << incomplete << endl;
	aIO.fileClose();
	aIO2.fileClose();
	bIO.fileClose();
}