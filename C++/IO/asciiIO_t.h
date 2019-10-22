#include "virtIO_t.h"
#ifndef ASCIIIO_T_H
#define ASCIIIO_T_H

class asciiIO_t {
		public:
			virtual asciiIO_t() {}
			virtual asciiIO_t(const string path, const char* accessMode) {}
			virtual void fileOpen(const string path, const char* accessMode) {}
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
			virtual ~asciiIO_t();
		protected:
			FILE* fp;
			const string path;
			const char accessMode[2];
			IOStatus status;
		private:
			asciiIO_t(const asciiIO_t& other);
			asciiIO_t& operator=(const asciiIO_t& other);

};

#endif