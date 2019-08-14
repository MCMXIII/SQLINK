#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "times.h"

struct cTime_t {
	int m_hour;
	int m_minute;
	int m_second;
};
struct cDate_t {
	int m_day;
	int m_month;
	int m_year;
};
int validateTime(int h, int m, int s)
{
	if(h > 23 || m > 59 || s > 59 || h < 0 || m < 0 || s < 0)
	{
		return -1;
	}
	return 1;
}
cTime setTime(cTime t, int h, int m, int s)
{
	if(validateTime(h, m, s) < 0)
	{
		printf("Invalid values for time!\n");
		return t;
	}
	t->m_hour = h;
	t->m_minute = m;
	t->m_second = s;
	return t;
}
int printTime(cTime t, char format)
{
	if(validateTime(t->m_hour, t->m_minute, t->m_second) < 0)
	{
		printf("Invalid time!\n");
		return -1;
	}
	switch(format)
	{
		case 'a':
		{
			printf("%d:", t->m_hour);
			if(t->m_minute < 10)
			{
				putchar('0');
			}
			printf("%d:", t->m_minute);
			if(t->m_second < 10)
			{
				putchar('0');
			}
			printf("%d\n", t->m_second);
			break;
		}
		case 'b':
		{
			printf("%d:", ((11+t->m_hour)%12)+1);
			if(t->m_minute < 10)
			{
				putchar('0');
			}
			printf("%d:", t->m_minute);
			if(t->m_second < 10)
			{
				putchar('0');
			}
			printf("%d ", t->m_second);
			if(t->m_hour < 12)
			{
				printf("AM\n");
			}
			else
			{
				printf("PM\n");
			}
			break;
		}
		default:
		{
			printf("Invalid time format!\n");
			break;
		}
	}
	return 0;
}
int getHour(cTime t)
{
	return t->m_hour;
}
int getMinute(cTime t)
{
	return t->m_minute;
}
int getSecond(cTime t)
{
	return t->m_second;
}
cTime addTimes(cTime t1, cTime t2)
{
	if(validateTime(t1->m_hour, t1->m_minute, t1->m_second) + validateTime((t2->m_hour%24), t2->m_minute, t2->m_second) < 2)
	{
		printf("Invalid time!\n");
			return t1;
	}
	if((t1->m_second + t2->m_second) >= 60)
	{
		t1->m_minute++;
	}
	t1->m_second = (t1->m_second + t2->m_second)%60;
	if((t1->m_minute + t2->m_minute) >= 60)
	{
		t1->m_hour++;
	}
	t1->m_minute = (t1->m_minute + t2->m_minute)%60;
	t1->m_hour = (t1->m_hour + t2->m_hour)%24;
	return t1;
}
int validateDate(int d, int m, int y)
{
	int days[13]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(y % 4 == 0 && (y % 100 != 0 || y % 400 == 0))
	{
		days[2]++;
	}
	if( m < 1 || m > 12 || d < 0 || d > days[m])
	{
		return -1;
	}
	return 1;
}
cDate setDate(cDate date, int d, int m, int y)
{
	if(validateDate(d, m, y) < 0)
	{
		printf("Invalid values for date!\n");
		return date;
	}
	date->m_day = d;
	date->m_month = m;
	date->m_year = y;
	return date;
}
int printDate(cDate d, char format)
{
	char* names[13] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	if(validateDate(d->m_day, d->m_month, d->m_year) < 0)
	{
		printf("Invalid values for date!\n");
		return -1;
	}
	switch(format)
	{
		case 'a':
		{
			printf("%d/%s/%d\n", d->m_day, names[d->m_month], d->m_year);
			break;
		}
		case 'b':
		{
			if(d->m_day < 10)
			{
				putchar('0');
			}
			printf("%d/", d->m_day);
			if(d->m_month < 10)
			{
				putchar('0');
			}
			printf("%d/%d\n", d->m_month, d->m_year);
			break;
		}
		case 'c':
		{

			if(d->m_month < 10)
			{
				putchar('0');
			}
			printf("%d/", d->m_month);
			if(d->m_day < 10)
			{
				putchar('0');
			}
			printf("%d/%d\n", d->m_day, d->m_year);
			break;
		}
		default:
		{
			printf("Invalid time format!\n");
			break;
		}
	}
	return 0;
}
int getDay(cDate d)
{
	return d->m_day;
}
int getMonth(cDate d)
{
	return d->m_month;
}
int getYear(cDate d)
{
	return d->m_year;
}
int getLeap(cDate d)
{
	return d->m_year % 4 == 0 && (d->m_year % 100 != 0 || d->m_year % 400 == 0);
}
int getCurrentDay()
{
	time_t time_date;
	struct tm* current_time;
	time_date = time(0);
	current_time = localtime(&time_date);
	return current_time->tm_mday;
}
int getCurrentMonth()
{
	time_t time_date;
	struct tm* current_time;
	time_date = time(0);
	current_time = localtime(&time_date);
	return current_time->tm_mon + 1;
}
int getCurrentYear()
{
	time_t time_date;
	struct tm* current_time;
	time_date = time(0);
	current_time = localtime(&time_date);
	return current_time->tm_year + 1900;
}
int getDayOfYear(cDate d)
{
	int days[13]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int dayOfYear = 0;
	int i;
	if(validateDate(d->m_day, d->m_month, d->m_year) < 0)
	{
		printf("Invalid values for date!\n");
		return -1;
	}
	for(i = 1; i < d->m_month; i++)
	{
		dayOfYear+=days[i];
		if(i == 2 && getLeap(d))
		{
			dayOfYear++;
		}
	}
	dayOfYear+=d->m_day;
	return dayOfYear;
}
cTime allocTime()
{
	return (cTime)malloc(sizeof(struct cTime_t));
}
cDate allocDate()
{
	return (cDate)malloc(sizeof(struct cDate_t));
}
cDate addDays(cDate d, int days)
{
	int daysArr[13]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	while(days > 0)
	{
		if(d->m_day == daysArr[d->m_month] || (d->m_day == 29 && d->m_month == 2))
		{
			if(d->m_month == 12)
			{
				setDate(d, 1, 1, getYear(d) + 1);
			}
			else if(d->m_month == 2 && getLeap(d))
			{
				if(d->m_day == 28)
				{
					setDate(d, 29, 2, getYear(d));
				}
				else
				{
					setDate(d, 1, 3, getYear(d));
				}
			}
			else
			{
				setDate(d, 1, getMonth(d) + 1, getYear(d));
			}
		}
		else
		{
			setDate(d, getDay(d) + 1, getMonth(d), getYear(d));
		}
		days--;
	}
	return d;
}
int addTimeToDate(cDate d, cTime t, cTime interval)
{
	int additionalDays = 0;
	if(validateTime(t->m_hour, t->m_minute, t->m_second) + validateTime((interval->m_hour%24), interval->m_minute, interval->m_second) + validateDate(d->m_day, d->m_month, d->m_year) < 3)
	{
		printf("Invalid date or time!\n");
		return -1;
	}
	if((t->m_second + interval->m_second) >= 60)
	{
		t->m_minute++;
	}
	t->m_second = (t->m_second + interval->m_second)%60;
	if((t->m_minute + interval->m_minute) >= 60)
	{
		t->m_hour++;
	}
	t->m_minute = (t->m_minute + interval->m_minute)%60;
	if((t->m_hour + interval->m_hour) >= 24)
	{
		additionalDays+=(t->m_hour + interval->m_hour)/24;
	}
	t->m_hour = (t->m_hour + interval->m_hour)%24;
	d = addDays(d, additionalDays);
	return 0;
}
