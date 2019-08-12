#include <stdio.h>
#include <stdlib.h>

#ifndef DIARY_H
#define DIARY_H

	typedef struct diary* diary;
	typedef struct meeting* meeting;
	diary createDiary();
	meeting createMeeting(float bhour, float ehour, int room);
	diary insert(diary d, meeting m);
	int findIndex(diary d, float beginHour);
	meeting find(diary d, float beginHour);
	diary mremove(diary d, float beginHour);
	int mprint(int i, diary d);
	int mprint2(meeting m, diary d);
	diary dprint(diary d);
	diary destroy(diary d);

#endif
