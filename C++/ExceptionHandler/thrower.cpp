#include <iostream>
#include "TException_t.h"

void throwInt()
{
	int x = 191312;
	throw(*(new TException_t<int>(x, "MCMXIII", __FILE__, __LINE__)));
}
void throwFloat()
{
	float x = 1913.12;
	throw(*(new TException_t<float>(x, "MCMXIII", __FILE__, __LINE__)));
}

int main()
{
	try
	{
		throwInt();
	}
	catch(TException_t<int> ex)
	{
		cout << "Int object: " << ex.getObject() << " (" << ex.getDescription() << ") in " << ex.getFileName() << ":" << ex.getLine() << "\n";
		try
		{
			throwFloat();
		}
		catch(TException_t<float> ex)
		{
			cout << "Float object: " << ex.getObject() << " (" << ex.getDescription() << ") in " << ex.getFileName() << ":" << ex.getLine() << "\n";
		}
	}
}