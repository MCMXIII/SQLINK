#include <iostream>
#include <string>
#ifndef CAR_H
#define CAR_H

typedef enum { Unset, Standard, Automatic } gearType;

using namespace std;
class car_t
{
	public:
		car_t();
		car_t(string n, unsigned int c);
		car_t(const car_t& other);
		car_t& operator=(const car_t& other);
		bool operator<(const car_t& other) { return capacity < other.capacity; }
		bool operator>(const car_t& other) { return capacity > other.capacity; }
		bool operator<=(const car_t& other) { return capacity <= other.capacity; }
		bool operator>=(const car_t& other) { return capacity >= other.capacity; }
		bool operator==(const car_t& other) { return capacity == other.capacity; }
		bool operator!=(const car_t& other) { return capacity != other.capacity; }
		bool compare(const car_t& other) const { return name.compare(other.name) == 0; }
		unsigned int getId() { return carId; }
		string getName() { return name; }
		gearType getGear() { return gear; }
		void setGear(gearType g) { if(g != Unset) {if(gear == Unset) gear = g; else cout<<"Cannot change gear!\n"; } else cout<<"Cannot set gear to Unset!\n"; }
		unsigned int getCapacity() { return capacity; }
		void setCapacity(unsigned int c) { capacity = c; }
	protected:
		~car_t() {}
		static unsigned int generateId() { int newId = id++; return newId; }
	private:
		static unsigned int id;
		unsigned int carId;
		string name;
		unsigned int capacity;
		gearType gear;
};
	/*ostream& operator<<(ostream& os, const stringType& s);
	istream& operator>>(istream& is, stringType& s);*/
#endif