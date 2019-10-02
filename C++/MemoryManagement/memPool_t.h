#include "memManager_t.h"
#include "memPage_t.h"
#include <vector>

#ifndef MEMPOOL_T_H
#define MEMPOOL_T_H

using namespace std;
class memPool_t : memManager_t
{
	public:
		memPool_t(unsigned int cap) { size = 0; position = 0; capacity = cap; pbuffer.insert(pbuffer.end(), new memPage_t(capacity));  }
		virtual ~memPool_t() { int i; for(i = 0; i <= size/capacity; i++) delete pbuffer[i]; }
		virtual char* read(void* output, unsigned int bytes);
		virtual char* read(void* output, const unsigned int pos, unsigned int bytes);
		virtual unsigned int write(const void* bytes, unsigned int amountToWrite);
		virtual unsigned int write(const unsigned int pos, const void* bytes , unsigned int amountToWrite);
		unsigned int getCapacity() const { return capacity; }
		void setCapacity(unsigned int newCap);
	private:
		vector<memPage_t*> pbuffer;
		unsigned int capacity;
		/*unsigned int size;
		unsigned int position;*/
};

#endif