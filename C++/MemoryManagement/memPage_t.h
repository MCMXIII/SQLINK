#include "memManager_t.h"

#ifndef MEMPAGE_T_H
#define MEMPAGE_T_H

using namespace std;
class memPage_t : memManager_t
{
	public:
		memPage_t(unsigned int cap) { size = 0; position = 0; capacity = cap; buffer = new char[cap]; }
		virtual ~memPage_t() { delete [] buffer; }
		bool isFull() const { return size == capacity; }
		unsigned int getCapacity() const { return capacity; }
		/*void setCapacity(unsigned int newCap);*/
		virtual char* read(void* output, unsigned int bytes);
		virtual char* read(void* output, const unsigned int pos, unsigned int bytes);
		virtual unsigned int write(const void* bytes, unsigned int amountToWrite);
		virtual unsigned int write(const unsigned int pos, const void* bytes , unsigned int amountToWrite);
	private:
		char* buffer;
		unsigned int capacity;
		/*unsigned int size;
		unsigned int position;*/
};

#endif