#include <iostream>
#include <string>
#include "car.h"
#ifndef PRIVATE_H
#define PRIVATE_H


using namespace std;
class private_t:public car_t
{
	public:
		private_t();
		bus_t(unsigned int c, unsigned int s, unsigned int l);
		bus_t(const bus_t& other);
		bus_t& operator=(const bus_t& other);
		unsigned int getSeats() { return seats; }
		void setSeats(unsigned int s) { seats = s; }
		unsigned int getLine() { return line; }
		void setLine(unsigned int l) { line = l; }
		~bus_t() {}
	private:
		unsigned double speed;
};
	/*ostream& operator<<(ostream& os, const stringType& s);
	istream& operator>>(istream& is, stringType& s);*/
#endif
