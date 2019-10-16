#include "calendar_t.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <iterator>

using namespace std;
const Meeting_t* Calendar_t::nextIndex(const float& hour)
{
	int i;
	map<float, Meeting_t*, Compare>::iterator it = day.begin();
	for(i = 0; i < day.size(); i++)
	{
		if((*(it->second)).getBegin() >= hour)
		{
			return it->second;
		}
		it++;
	}
	return 0;
}
const Meeting_t* Calendar_t::previousIndex(const float& hour)
{
	int i;
	map<float, Meeting_t*, Compare>::reverse_iterator it = day.rbegin();
	for(i = 0; i < day.size(); i++)
	{
		if((*(it->second)).getBegin() <= hour)
		{
			return it->second;
		}
		it++;
	}
	return 0;
}
void Calendar_t::insert(Meeting_t* meeting)
{
	const Meeting_t* next = nextIndex((*meeting).getBegin());
	const Meeting_t* previous = previousIndex((*meeting).getBegin());
	if(meeting != 0 && (next == 0 || (*next).getBegin() >= (*meeting).getEnd()) && (previous == 0 || (*previous).getEnd() <= (*meeting).getBegin()))
	{
		day[(*meeting).getBegin()] = meeting;
	}
	else
	{
		cout << "There's a collision with other meetings or day bounds!\n";
	}
}
const Meeting_t* Calendar_t::remove(const float& hour)
{
	map<float, Meeting_t*, Compare>::iterator it = day.find(hour);
	Meeting_t* m = (it == day.end())?0:it->second;
	if(it != day.end())
	{
		day.erase(hour);
	}
	else
	{
		cout << "Nothing to erase!\n";
	}
	return m;
}
const Meeting_t* Calendar_t::find(const float& hour)
{
	map<float, Meeting_t*, Compare>::iterator it = day.find(hour);
	Meeting_t* m = (it == day.end())?0:it->second;
	if(it == day.end())
	{
		cout << "Not found!\n";
	}
	return m;
}
void Calendar_t::clean()
{
	Meeting_t** arr = new Meeting_t*[day.size()];
	int i;
	map<float, Meeting_t*, Compare>::iterator it = day.begin();
	for(i = 0; i < day.size(); i++)
	{
		arr[i] = it->second;
		it++;
	}
	Calendar_t::day.clear();
	for(i = 0; i < day.size(); i++)
	{
		delete arr[i];
	}
	delete arr;
}
void Calendar_t::writeToFile(const char* name)
{
	std::fstream fs;
	fs.open(name, std::fstream::out);
	map<float, Meeting_t*, Compare>::iterator it;
	for(it = day.begin(); it != day.end(); it++)
	{
		if(it != day.begin()) fs << "\n";
		fs << "Begin:" << it->first << "-End:" << (*(it->second)).getEnd() << "-Subject:" << (*(it->second)).getSubject();
	}
	fs.close();
}
void Calendar_t::readFromFile(const char* name)
{
	string line;
	clean();
	std::fstream fs;
	fs.open(name, std::fstream::in);
	while(getline(fs, line))
	{
		float b = strtof((line.substr(6,(line.find_first_of('-')-6))).c_str(), 0);
		line = line.substr(line.find_first_of('-') + 1, line.length());
		float e = strtof((line.substr(4,(line.find_first_of('-')-4))).c_str(), 0);
		line = line.substr(line.find_first_of('-') + 1, line.length());
		string subject = line.substr(8,line.length());
		insert(new Meeting_t(b, e, string(subject)));
	}
	fs.close();
}