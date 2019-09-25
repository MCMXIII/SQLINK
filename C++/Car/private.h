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
		private_t(unsigned int c, double s);
		private_t(const private_t& other);
		private_t& operator=(const private_t& other);
		double getSpeed() { return speed; }
		void setSpeed(double s) { speed = s; }
		void accelerate() { speed+=10.0; }
		void reduceSpeed() { speed-=10.0; }
		~private_t() {}
	private:
		double speed;
};
	/*ostream& operator<<(ostream& os, const stringType& s);
	istream& operator>>(istream& is, stringType& s);*/
#endif