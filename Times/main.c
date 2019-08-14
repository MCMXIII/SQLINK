#include <stdio.h>
#include <stdlib.h>
#include "times.h"

int main()
{
	cTime t1 = allocTime();
	cTime t2;
	cDate d;
	int h = 24;
	int m = 60;
	int s = 60;
	int da = 32;
	int mo = 13;
	int y = 0;
	char f = 'd';
	if(t1 == NULL)
	{
		return -1;
	}
	while(h > 23 || m > 59 || s > 59 || h < 0 || m < 0 || s < 0)
	{
		printf("Enter a time (hh:mm:ss):\n");
		scanf("%d:%d:%d", &h, &m, &s);
		setTime(t1, h, m, s);
	}
	while(f != 'a' && f != 'b')
	{
		if(f != 'a' && f != 'b')
		{
			if(f == 'd')
			{
				printf("Enter a time format (a or b):\n");
			}
			f = 'e';
			scanf("%c", &f);
		}
		if(f == 'a' || f == 'b')
		{
			printTime(t1, f);
		}
	}

	printf("Hours: %d, minutes: %d, seconds: %d\n", getHour(t1), getMinute(t1), getSecond(t1));
	t2 = allocTime();
	if(t2 == NULL)
	{
		return -1;
	}
	h = 24;
	m = 60;
	s = 60;
	while(h > 23 || m > 59 || s > 59 || h < 0 || m < 0 || s < 0)
	{
		printf("Enter a time (hh:mm:ss):\n");
		scanf("%d:%d:%d", &h, &m, &s);
		setTime(t2, h, m, s);
	}
	addTimes(t1, t2);
	printTime(t1, f);
	d=allocDate();
	setDate(d, 1, 1, -1);
	while(getYear(d) == -1)
	{
		printf("Enter a date AC (dd/mm/yyyy):\n");
		scanf("%d/%d/%d", &da, &mo, &y);
		setDate(d, da, mo, y);
	}
	f = 'd';
	while(f != 'a' && f != 'b' && f != 'c')
	{
		if(f != 'a' && f != 'b' && f != 'c')
		{
			if(f == 'd')
			{
				printf("Enter a date format (a, b or c):\n");
			}
			f = 'e';
			scanf("%c", &f);
		}
		if(f == 'a' || f == 'b' || f == 'c')
		{
			printDate(d, f);
		}
	}
	printf("Day: %d, month: %d, year: %d\n", getDay(d), getMonth(d), getYear(d));
	printf("%s\n", getLeap(d)?"It's a leap year":"It's not a leap year");
	printf("Current date %d/%d/%d\n", getCurrentDay(), getCurrentMonth(), getCurrentYear());
	printf("This is day number %d in %d\n", getDayOfYear(d), getYear(d));
	printf("Enter amount of days to add to your date:\n");
	scanf("%d", &da);
	addDays(d, da);
	printDate(d, f);
	h = 24;
	m = 60;
	s = 60;
	while(h > 23 || m > 59 || s > 59 || h < 0 || m < 0 || s < 0)
	{
		printf("Enter a time (hh:mm:ss):\n");
		scanf("%d:%d:%d", &h, &m, &s);
		setTime(t1, h, m, s);
	}
	h = 24;
	m = 60;
	s = 60;
	while(h > 23 || m > 59 || s > 59 || h < 0 || m < 0 || s < 0)
	{
		printf("Enter a time (hh:mm:ss):\n");
		scanf("%d:%d:%d", &h, &m, &s);
		setTime(t2, h, m, s);
	}
	setDate(d, 1, 1, -1);
	while(getYear(d) == -1)
	{
		printf("Enter a date AC (dd/mm/yyyy):\n");
		scanf("%d/%d/%d", &da, &mo, &y);
		setDate(d, da, mo, y);
	}
	addTimeToDate(d, t1, t2);
	printDate(d, f);
	if(f == 'c')
	{
		printTime(t1, 'a');
	}
	else
	{
		printTime(t1, f);
	}
	free(t1);
	free(t2);
	free(d);
	return 0;
}
