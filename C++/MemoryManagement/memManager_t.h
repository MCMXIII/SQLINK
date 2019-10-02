#ifndef MEMMANAGER_T_H
#define MEMMANAGER_T_H

using namespace std;
class memManager_t
{
	public:
		memManager_t() { size = 0; position = 0; }
		unsigned int getPosition() { return position; }
		void setPosition(const unsigned int p) { if(p <= size) position = p; }
		bool isEmpty() const { return size == 0; }
		unsigned int getSize() const { return size; }
		virtual char* read(/*const void* buffer, */void* output, unsigned int bytes) { return 0; }
		virtual char* read(/*const void* buffer, */void* output, const unsigned int pos, unsigned int bytes) { return 0; }
		virtual unsigned int write(/*void* buffer, */const void* bytes , unsigned int amountToWrite) { return 0; }
		virtual unsigned int write(/*void* buffer, */const unsigned int pos, const void* bytes, unsigned int amountToWrite) { return 0; }
	protected:
		virtual ~memManager_t() {}
		unsigned int size;
		unsigned int position;
	private:
};

#endif