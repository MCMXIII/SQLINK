#include "virtIO_t.h"
#include <string.h>
#ifndef ASCIIIO_T_H
#define ASCIIIO_T_H

class asciiIO_t:public virtIO_t {
		public:
			asciiIO_t():virtIO_t() {}
			asciiIO_t(const string p, const char* access):virtIO_t(p, access) { strcpy(accessMode, access); fp = fopen(path.c_str(), accessMode); if(fp == 0) setStatus(cant_open_file_e); else setStatus(ok_e); }
			void fileOpen(const string p, const char* access) {if(fp == 0){setPath(p); setAccessMode(access); fp = fopen(path.c_str(), accessMode); if(fp == 0) setStatus(cant_open_file_e); else setStatus(ok_e);} }
			asciiIO_t& operator<<(const int value);
			asciiIO_t& operator<<(const char value);
			asciiIO_t& operator<<(const short value);
			asciiIO_t& operator<<(const long value);
			asciiIO_t& operator<<(const unsigned int value);
			asciiIO_t& operator<<(const unsigned char value);
			asciiIO_t& operator<<(const unsigned short value);
			asciiIO_t& operator<<(const unsigned long value);
			asciiIO_t& operator<<(const float value);
			asciiIO_t& operator<<(const double value);
			asciiIO_t& operator>>(int& value);
			asciiIO_t& operator>>(char& value);
			asciiIO_t& operator>>(short& value);
			asciiIO_t& operator>>(long& value);
			asciiIO_t& operator>>(unsigned int& value);
			asciiIO_t& operator>>(unsigned char& value);
			asciiIO_t& operator>>(unsigned short& value);
			asciiIO_t& operator>>(unsigned long& value);
			asciiIO_t& operator>>(float& value);
			asciiIO_t& operator>>(double& value);
			~asciiIO_t() {}
		private:
			asciiIO_t(const asciiIO_t& other) {}
			asciiIO_t& operator=(const asciiIO_t& other) {}

};

#endif