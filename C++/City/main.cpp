#include "City_t.h"
#include "Street_t.h"
#include "Building_t.h"
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;
int main()
{
	Street_t<string, unsigned int> s("Pinchas & Abraham Rothenberg");
	City_t<string, string, unsigned int> c("Haifa");
	c.addStreet(s);
	c.addStreet("Pika");
	cout << c.getId() << "\n";
	cout << c.getStreet("Pinchas & Abraham Rothenberg").getId() << "\n";
	c.getStreet("Pika").addBuilding(1913);
	cout << c.getStreet("Pika").getBuilding(1913).getId() << "\n";
	c.getStreet("Pinchas & Abraham Rothenberg").addBuilding(c.getStreet("Pika").getBuilding(1913));
	cout << c.getStreet("Pinchas & Abraham Rothenberg").getBuilding(1913).getId() << "\n";
}