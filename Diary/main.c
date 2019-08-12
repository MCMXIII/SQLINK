#include "diary.h"

int main()
{
	diary d;
	meeting m;
	char action = 'x';
	float bh, eh;
	int bhh, bmm, ehh, emm;
	int r;
	d = createDiary();
	while(action != 'q')
	{
		if(action == 'x')
		{
			printf("i - insert, r - remove, f - find, p - print, q - quit\n");
			action = 'z';
		}
		scanf("%c", &action);
		if(action == 'q')
		{
			destroy(d);
			free(m);
			break;
		}
		if(action == 'i')
		{
			printf("Enter begin time (hh:mm):\n");
			scanf("%d:%d", &bhh, &bmm);
			bh = bhh + (((float)bmm)/60);
			printf("Enter end time (hh:mm):\n");
			scanf("%d:%d", &ehh, &emm);
			eh = ehh + (((float)emm)/60);
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
			bh = bhh + (((float)bmm)/60);
			d = mremove(d, bh);
			action = 'x';
		}
		if(action == 'f')
		{
			printf("Enter begin time (hh:mm):\n");
			scanf("%d:%d", &bhh, &bmm);
			bh = bhh + (((float)bmm)/60);
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
