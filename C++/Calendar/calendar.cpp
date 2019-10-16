#include "calendar_t.h"
#include <iostream>
#include <string>

using namespace std;
int main()
{
	Calendar_t calendar;
	calendar.readFromFile("calendar.log");
	unsigned int action = -1;
	float b;
	float e;
	/*char sub[512];*/
	string subject;
	while(action > 0)
	{
		cout << "1 to insert a new meeting, 2 to remove a meeting from the day, 3 to find a meeting starting on a specific time, 4 to clean the meetings day, 0 to exit.\n";
		cin >> action;
		switch(action)
		{
			case 0:
				calendar.writeToFile("calendar.log");
				calendar.clean();
				break;
			case 1:
				cout << "Enter a begin hour:\n";
				cin >> b;
				cout << "Enter an end hour:\n";
				cin >> e;
				cout << "Enter a subject for the meeting:\n";
				cin.ignore();
				getline(cin,subject,'\n');
				/*subject = sub;*/
				try { calendar.insert(new Meeting_t(b, e, string(subject))); } catch(string ex) { cout << ex; }
				break;
			case 2:
				cout << "Enter a begin hour:\n";
				cin >> b;
				calendar.remove(b);
				break;
			case 3:
				cout << "Enter a begin hour:\n";
				cin >> b;
				if(calendar.find(b) != 0)
				{
					cout << "Begin: " << (*(calendar.find(b))).getBegin() << "\nEnd: " << (*(calendar.find(b))).getEnd() << "\nSubject: " << (*(calendar.find(b))).getSubject() << "\n";
				}
				break;
			case 4:
				calendar.clean();
				break;
			default: break;
		}
	}
	return 0;
}