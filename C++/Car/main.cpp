#include "bus.h"
#include <stdio.h>
#include <iostream>

using namespace std;
int main()
{
	bus_t b1(1500, 52, 1913);
	bus_t b2(b1);
	bus_t b3(2000, 54, 1312);
	cout << b1.getName() << "\n";
	cout << b2.getName() << "\n";
	cout << b1.getId() << "\n";
	cout << b2.getId() << "\n";
	cout << b1.getCapacity() << "\n";
	cout << b2.getCapacity() << "\n";
	cout << b1.getSeats() << "\n";
	cout << b2.getSeats() << "\n";
	cout << b1.getLine() << "\n";
	cout << b2.getLine() << "\n";
	b1.setGear(Unset);
	b1.setGear(Standard);
	b1.setGear(Automatic);
	b2.setGear(Automatic);
	b3.setGear(Standard);
	cout << b1.getGear() << "\n";
	cout << b2.getGear() << "\n";
	b2 = b3;
	cout << b2.getName() << "\n";
	cout << b2.getId() << "\n";
	cout << b2.getCapacity() << "\n";
	cout << b2.getSeats() << "\n";
	cout << b2.getLine() << "\n";
	cout << b2.getGear() << "\n";
}