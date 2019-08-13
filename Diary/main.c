#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "diary.h"

int main()
{
	diary d;
	meeting m = 0;
	char action = 'x';
	float bh, eh;
	int bhh, bmm, ehh, emm;
	int r;
	/*d = createDiary();*/
	d = loadFromFile();
	while(action != 'q')
	{
		if(action == 'x')
		{
			printf("i - insert, r - remove, f - find, p - print, s - save, q - quit\n");
			action = 'z';
		}
		scanf("%c", &action);
		if(action == 'q')
		{
			saveAndClose(d);
			if(m != 0)
			{
				free(m);
			}
			break;
		}
		if(action == 's')
		{
			saveToFile(d);
			action = 'x';
		}
		if(action == 'i')
		{
			printf("Enter begin time (hh:mm):\n");
			scanf("%d:%d", &bhh, &bmm);
			bh = bhh + ((ceil(100*((float)bmm))/100)/60);
			printf("Enter end time (hh:mm):\n");
			scanf("%d:%d", &ehh, &emm);
			eh = ehh + /*(((float)emm)*/((ceil(100*((float)emm))/100)/60);
			printf("Enter room number:\n");
			scanf("%d", &r);
			m = createMeeting(bh, eh, r);
			d = insert(d, m);
			action = 'x';
		}
		if(action == 'r')
		{
			printf("Enter begin time (hh:mm):\n");
			scanf("%d:%d", &bhh, &bmm);
			bh = bhh + ((ceil(100*((float)bmm))/100)/60);
			d = mremove(d, bh);
			action = 'x';
		}
		if(action == 'f')
		{
			printf("Enter begin time (hh:mm):\n");
			scanf("%d:%d", &bhh, &bmm);
			bh = bhh + ((ceil(100*((float)bmm))/100)/60);
			m = find(d, bh);
			mprint2(m, d);
			action = 'x';
		}
		if(action == 'p')
		{
			dprint(d);
			action = 'x';
		}
	}

	return 0;
}
