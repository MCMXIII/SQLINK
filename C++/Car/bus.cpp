#include <ctype.h>
#include <stdlib.h>
#include "bus.h"

bus_t::bus_t():car_t(*(new string("Bus")), 0)
{
	seats = 0;
	line = 0;
}
bus_t::bus_t(unsigned int c, unsigned int s, unsigned int l):car_t(*(new string("Bus")), c)
{
	seats = s;
	line = l;
}
bus_t::bus_t(const bus_t& other):car_t((car_t&)other)
{
	seats = other.seats;
	line = other.line;
}
bus_t& bus_t::operator=(const bus_t& other)
{
	car_t::operator=((car_t&) other);
	seats = other.seats;
	line = other.line;
	return *this;
}