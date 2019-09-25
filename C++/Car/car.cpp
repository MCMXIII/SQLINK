#include <ctype.h>
#include <stdlib.h>
#include "car.h"

unsigned int car_t::id = 0;
car_t::car_t()
{
	carId = generateId();
	name = "";
	capacity = 0;
	gear = Unset;
}
car_t::car_t(string n, unsigned int c)
{
	carId = generateId();
	name = n;
	capacity = c;
	gear = Unset;
}
car_t::car_t(const car_t& other)
{
	carId = generateId();
	name = other.name;
	capacity = other.capacity;
	gear = other.gear;
}
car_t& car_t::operator=(const car_t& other)
{
	if(*this != other)
	{
		capacity = other.capacity;
		if(gear == Unset && other.gear != Unset)
		{
			gear = other.gear;
		}
	}
	return *this;
}
/*std::ostream& operator<<(std::ostream& os, const stringType& s)
{
	os << s.getString();
	return os;
}
std::istream& operator>>(std::istream& is, stringType& s)
{
	char st[128];
	is >> st;
	s.setString(st);
	return is;
}*/