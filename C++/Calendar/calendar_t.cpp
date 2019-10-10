#include "calendar_t.h"

const int& nextIndex(const float& hour)
{
	int i;
	for(i = 0; i < day.size(); i++)
	{
		if(day[i]->begin > hour)
		{
			return i;
		}
	}
	return i;
}
void Calendar_t::insert(const Meeting_t* meeting)
{
	if()
}
const Meeting_t* Calendar_t::remove(const Meeting_t* meeting);
const Meeting_t* Calendar_t::find(const float& hour)
