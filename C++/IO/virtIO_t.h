#include <stdio.h>
#include <string>
#ifndef VIRTIO_T_H
#define VIRTIO_T_H

typedef enum{ok_e, cant_open_file_e, bad_access_e, writeErr_e, readErr_e} IOStatus;

class virtIO_t {
		public:
			virtual virtIO_t() = 0;
			virtual virtIO_t(const string path, const char* accessMode) = 0;
			virtual void fileOpen(const string path, const char* accessMode) = 0;
			void fileClose(){if(fp != 0) fclose(fp);}
			const string getPath() const {return path;}
			const char* getAccess() const {return accessMode;}
			virtual unsigned long getLength() const;
			virtual unsigned long getPosition() const {return ftell(fp);}
			virtual void setPosition(const unsigned long& newPosition){fseek(fp, newPosition, SEEK_SET);}
			virtual IOStatus getStatus() const {return status;};
			virtual void setStatus(const IOStatus& newStatus){status = newStatus};
			virtual virtIO_t& operator<<(int value);
			virtual virtIO_t& operator<<(char value);
			virtual virtIO_t& operator<<(short value);
			virtual virtIO_t& operator<<(long value);
			virtual virtIO_t& operator<<(unsigned int value);
			virtual virtIO_t& operator<<(unsigned char value);
			virtual virtIO_t& operator<<(unsigned short value);
			virtual virtIO_t& operator<<(unsigned long value);
			virtual virtIO_t& operator<<(float value);
			virtual virtIO_t& operator<<(double value);
			virtual virtIO_t& operator>>(int& value);
			virtual virtIO_t& operator>>(char& value);
			virtual virtIO_t& operator>>(short& value);
			virtual virtIO_t& operator>>(long& value);
			virtual virtIO_t& operator>>(unsigned int& value);
			virtual virtIO_t& operator>>(unsigned char& value);
			virtual virtIO_t& operator>>(unsigned short& value);
			virtual virtIO_t& operator>>(unsigned long& value);
			virtual virtIO_t& operator>>(float& value);
			virtual virtIO_t& operator>>(double& value);
		protected:
			virtual ~virtIO_t();
			FILE* fp;
			const string path;
			const char accessMode[2];
			IOStatus status;
		private:
			virtIO_t(const virtIO_t& other);
			virtIO_t& operator=(const virtIO_t& other);

};

virtual unsigned long virtIO_t::getLength() const
{
	unsigned long oldPosition = ftell(fp);
	char c = ' ';
	while(c != EOF)
		c = fgetc(fp);
	ftell(fp)
}

#endif