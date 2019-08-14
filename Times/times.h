#ifndef TIMES_H
#define TIMES_H

	typedef struct cTime_t* cTime;
	typedef struct cDate_t* cDate;
	cTime setTime(cTime t, int h, int m, int s);
	int printTime(cTime t, char format);
	int getHour(cTime t);
	int getMinute(cTime t);
	int getSecond(cTime t);
	cTime addTimes(cTime t1, cTime t2);
	cDate setDate(cDate date, int d, int m, int y);
	int printDate(cDate d, char format);
	int getDay(cDate d);
	int getMonth(cDate d);
	int getYear(cDate d);
	int getLeap(cDate d);
	int getCurrentDay();
	int getCurrentMonth();
	int getCurrentYear();
	int getDayOfYear(cDate d);
	cTime allocTime();
	cDate allocDate();
	cDate addDays(cDate d, int days);
	int addTimeToDate(cDate d, cTime t, cTime interval);

#endif
