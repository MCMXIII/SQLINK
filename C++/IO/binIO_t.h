#include "virtIO_t.h"
#include <string.h>
#ifndef BINIO_T_H
#define BINIO_T_H

class binIO_t:public virtIO_t {
		public:
			binIO_t():virtIO_t() { rwBuffer = 0; }
			binIO_t(const string p, const char* access):virtIO_t(p, access) { rwBuffer = 0; strcpy(accessMode, access); char binary[4]; strcpy(binary, accessMode); binary[2] = 'b'; binary[3] = '\0'; fp = fopen(path.c_str(), binary); if(fp == 0) setStatus(cant_open_file_e); else setStatus(ok_e); }
			void fileOpen(const string p, const char* access) {if(fp == 0){path = p; strcpy(accessMode, access); char binary[4]; strcpy(binary, accessMode); binary[2] = 'b'; binary[3] = '\0'; fp = fopen(path.c_str(), binary); if(fp == 0) setStatus(cant_open_file_e); else setStatus(ok_e);} }
			binIO_t& operator<<(const int value);
			binIO_t& operator<<(const char value);
			binIO_t& operator<<(const short value);
			binIO_t& operator<<(const long value);
			binIO_t& operator<<(const unsigned int value);
			binIO_t& operator<<(const unsigned char value);
			binIO_t& operator<<(const unsigned short value);
			binIO_t& operator<<(const unsigned long value);
			binIO_t& operator<<(const float value);
			binIO_t& operator<<(const double value);
			binIO_t& operator<<(const void* buf);
			binIO_t& operator>>(int& value);
			binIO_t& operator>>(char& value);
			binIO_t& operator>>(short& value);
			binIO_t& operator>>(long& value);
			binIO_t& operator>>(unsigned int& value);
			binIO_t& operator>>(unsigned char& value);
			binIO_t& operator>>(unsigned short& value);
			binIO_t& operator>>(unsigned long& value);
			binIO_t& operator>>(float& value);
			binIO_t& operator>>(double& value);
			binIO_t& operator>>(void* buf);
			void operator,(int len);
			~binIO_t() {}
		private:
			bool isRead;
			void* rwBuffer;
			binIO_t(const binIO_t& other) {}
			binIO_t& operator=(const binIO_t& other) {}

};
#endif