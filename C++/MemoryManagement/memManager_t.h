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
		unsigned int getCapacity() const { return capacity; }
		virtual char* read(const void* buffer, unsigned int bytes) const;
		virtual char* read(const void* buffer, const unsigned int pos, unsigned int bytes) const;
		virtual int write(void* buffer, const char* bytes);
		virtual char write(void* buffer, const unsigned int pos, const char* bytes);
	protected:
		~memManager_t() {}
	private:
		unsigned int size;
		unsigned int position;
};

#endif
