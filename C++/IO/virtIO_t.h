#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#ifndef VIRTIO_T_H
#define VIRTIO_T_H

using namespace std;

typedef enum{ok_e, cant_open_file_e, bad_access_e, writeErr_e, readErr_e} IOStatus;

class virtIO_t {
		public:
			virtIO_t() { fp = 0; status = ok_e; }
			virtIO_t(const string p, const char* access) { path = p; }
			virtual void fileOpen(const string p, const char* access) = 0;
			void fileClose(){if(fp != 0) fclose(fp); accessMode[0] = 0; accessMode[1] = 0; path = ""; status = ok_e; fp = 0;}
			const string getPath() const {return path;}
			const char* getAccess() const {return accessMode;}
			virtual unsigned long getLength() const {
				unsigned long length;
				if(fp == 0)
					return 0;
				unsigned long oldPosition = ftell(fp);
				char c = ' ';
				while(c != EOF)
					c = fgetc(fp);
				length = ftell(fp);
				fseek(fp, oldPosition, SEEK_SET);
				return length;
			}
			virtual unsigned long getPosition() const { if (fp == 0) return 0; return ftell(fp);}
			virtual void setPosition(const unsigned long& newPosition){if(fp != 0) {if(fseek(fp, newPosition, SEEK_SET) != 0) {cout << "Seek error!\n"; status = bad_access_e;} else status = ok_e;}}
			virtual IOStatus getStatus() const {return status;}
			virtual void setStatus(const IOStatus& newStatus){status = newStatus;}
			virtual virtIO_t& operator<<(int value) = 0;
			virtual virtIO_t& operator<<(char value) = 0;
			virtual virtIO_t& operator<<(short value) = 0;
			virtual virtIO_t& operator<<(long value) = 0;
			virtual virtIO_t& operator<<(unsigned int value) = 0;
			virtual virtIO_t& operator<<(unsigned char value) = 0;
			virtual virtIO_t& operator<<(unsigned short value) = 0;
			virtual virtIO_t& operator<<(unsigned long value) = 0;
			virtual virtIO_t& operator<<(float value) = 0;
			virtual virtIO_t& operator<<(double value) = 0;
			virtual virtIO_t& operator>>(int& value) = 0;
			virtual virtIO_t& operator>>(char& value) = 0;
			virtual virtIO_t& operator>>(short& value) = 0;
			virtual virtIO_t& operator>>(long& value) = 0;
			virtual virtIO_t& operator>>(unsigned int& value) = 0;
			virtual virtIO_t& operator>>(unsigned char& value) = 0;
			virtual virtIO_t& operator>>(unsigned short& value) = 0;
			virtual virtIO_t& operator>>(unsigned long& value) = 0;
			virtual virtIO_t& operator>>(float& value) = 0;
			virtual virtIO_t& operator>>(double& value) = 0;
		protected:
			void setPath(const string p) { path = p; }
			void setAccessMode(const char* access) { strcpy(accessMode, access); }
			~virtIO_t() {  delete fp; /*delete [] accessMode;*/ }
			FILE* fp;
			string path;
			char accessMode[3];
			IOStatus status;
		private:
			virtIO_t(const virtIO_t& other) {}
			virtIO_t& operator=(const virtIO_t& other) {}

};


#endif