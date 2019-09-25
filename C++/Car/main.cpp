#include "bus.h"
#include "private.h"
#include <stdio.h>
#include <iostream>

using namespace std;
void printBus(bus_t& b)
{
	cout << "Name: " << b.getName() << " ID: " << b.getId() << " Capacity: " << b.getCapacity() << " Seats: " << b.getSeats() << " Line: " << b.getLine() << " Gear: " << b.getGear() << "\n";
}
void printPrivate(private_t& p)
{
	cout << "Name: " << p.getName() << " ID: " << p.getId() << " Capacity: " << p.getCapacity() << " Speed: " << p.getSpeed() << " Gear: " << p.getGear() << "\n";
}
int main()
{
	int action = -1;
	unsigned int uInput;
	double dInput;
	bus_t b1(1500, 52, 100);
	bus_t b2(b1);
	bus_t b3(2000, 54, 200);
	bus_t b4;
	private_t p1(1800, 121.7);
	private_t p2(p1);
	private_t p3(2000, 267.3);
	private_t p4;
	b1.setGear(Unset);
	b1.setGear(Standard);
	b1.setGear(Automatic);
	b2.setGear(Automatic);
	b3.setGear(Standard);
	b4.setGear(Automatic);
	cout << "b1: ";
	printBus(b1);
	cout << "b2: ";
	printBus(b2);
	cout << "b3: ";
	printBus(b3);
	cout << "b4: ";
	printBus(b4);
	cout << "p1: ";
	printPrivate(p1);
	cout << "p2: ";
	printPrivate(p2);
	cout << "p3: ";
	printPrivate(p3);
	cout << "p4: ";
	printPrivate(p4);
	cout << "b1<p1? " << (b1 < p1) << " p1>b1? " << (p1 > b1) << " b1<=p1? " << (b1 <= p1) << " b3>=p3? " << (b3 >= p3)  << " b1!=p1? " << (b1 != p1) << " b3==p3? " << (b3 == p3) << "\n";
	cout << "b1.compare(p1)? " << b1.compare(p1) << " b1.compare(b3)? " << b1.compare(b3) << " p1.compare(p3)? " << p1.compare(p3) << "\n";
	while(action != 0)
	{
		cout << "\n0 to exit, 1 to assign b3 into b2, 2 to assign p3 into p2, 3 to assign p1 into b1, 4 to set capacity of b1, 5 to set seats of b1, 6 to set line of b1, 7 to set speed of p1, 8 to accelerate b1, 9 to reduce speed of p1:\n";
		cin >> action;
		switch(action)
		{
			case 1: b2 = b3; break;
			case 2: p2 = p3; break;
			case 3: b1.car_t::operator=(p1); break;
			case 4:
				cout << "Enter new capacity:\n";
				cin >> uInput;
				b1.setCapacity(uInput);
				break;
			case 5:
				cout << "Enter new seats amount:\n";
				cin >> uInput;
				b1.setSeats(uInput);
				break;
			case 6:
				cout << "Enter new line number:\n";
				cin >> uInput;
				b1.setLine(uInput);
				break;
			case 7:
				cout << "Enter new speed:\n";
				cin >> dInput;
				p1.setSpeed(dInput);
				break;
			case 8: p1.accelerate(); break;
			case 9: p1.reduceSpeed(); break;
			default: break;
		}
		if(action >= 0 && action <= 9)
		{
			cout << "b1: ";
			printBus(b1);
			cout << "b2: ";
			printBus(b2);
			cout << "b3: ";
			printBus(b3);
			cout << "b4: ";
			printBus(b4);
			cout << "p1: ";
			printPrivate(p1);
			cout << "p2: ";
			printPrivate(p2);
			cout << "p3: ";
			printPrivate(p3);
			cout << "p4: ";
			printPrivate(p4);
			cout << "b1<p1? " << (b1 < p1) << " p1>b1? " << (p1 > b1) << " b1<=p1? " << (b1 <= p1) << " b3>=p3? " << (b3 >= p3)  << " b1!=p1? " << (b1 != p1) << " b3==p3? " << (b3 == p3) << "\n";
			cout << "b1.compare(p1)? " << b1.compare(p1) << " b1.compare(b3)? " << b1.compare(b3) << " p1.compare(p3)? " << p1.compare(p3) << "\n";
		}
	}/*
	b2 = b3;
	cout << "b1: ";
	printBus(b1);
	cout << "b2: ";
	printBus(b2);
	cout << "b3: ";
	printBus(b3);
	cout << "b4: ";
	printBus(b4);*/
}