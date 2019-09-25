#include <ctype.h>
#include <stdlib.h>
#include "private.h"

private_t::private_t():car_t(*(new string("Private")), 0)
{
	speed = 0.0;
}
private_t::private_t(unsigned int c, double s):car_t(*(new string("Private")), c)
{
	speed = s;
}
private_t::private_t(const private_t& other):car_t((car_t&)other)
{
	speed = other.speed;
}
private_t& private_t::operator=(const private_t& other)
{
	car_t::operator=((car_t&) other);
	speed = other.speed;
	return *this;
}