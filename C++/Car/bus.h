#include <iostream>
#include <string>
#include "car.h"
#ifndef BUS_H
#define BUS_H


using namespace std;
class bus_t:public car_t
{
	public:
		bus_t();
		bus_t(unsigned int c, unsigned int s, unsigned int l);
		bus_t(const bus_t& other);
		bus_t& operator=(const bus_t& other);
		unsigned int getSeats() { return seats; }
		void setSeats(unsigned int s) { seats = s; }
		unsigned int getLine() { return line; }
		void setLine(unsigned int l) { line = l; }
		~bus_t() {}
	private:
		unsigned int seats;
		unsigned int line;
};
	/*ostream& operator<<(ostream& os, const stringType& s);
	istream& operator>>(istream& is, stringType& s);*/
#endif