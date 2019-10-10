#include "calendar_t.h"
#include <iostream>
#include <string>

using namespace std;
int main()
{
	try
	{
		Meeting_t m(11.5, 13.5, "MCMXIII");
		cout << m.getBegin() << " " << m.getEnd() << " " << m.getSubject() << "\n";
	m.setSubject("MHFCMCMXIII");
	cout << m.getBegin() << " " << m.getEnd() << " " << m.getSubject() << "\n";
	}
	catch(string ex)
	{
		cout << ex;
	}
	try
	{
		Meeting_t m2(14.5, 14, "MTA");
	}
	catch(string ex)
	{
		cout << ex;
	}
	try
	{
		Meeting_t m2(-0.5, 10.5, "MTA1906");
	}
	catch(string ex)
	{
		cout << ex;
	}
	try
	{
		Meeting_t m2(23.5, 25.5, "1906");
	}
	catch(string ex)
	{
		cout << ex;
	}
	return 0;
}
