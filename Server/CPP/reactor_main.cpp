#include "reactor_t.h"
#include <iostream>
#include <string>

using namespace std;
int main()
{
	Reactor_t* reactor;
	Reactor_t::init(10);
	reactor = Reactor_t::getInstance();
	(*reactor).run();
}