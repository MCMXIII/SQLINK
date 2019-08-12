#include "diary.h"

struct meeting{
	float bhour;
	float ehour;
	int room;
};
struct diary{
	meeting* arr;
	int capacity;
	int amount;
};
diary createDiary()
{
	diary d = (diary)malloc(sizeof(struct diary));
	if (d == NULL)
	{
		printf("Error! Cannot create a diary.\n");
		return d;
	}
	d->capacity = 1;
	d->amount = 0;
	d->arr = (meeting*)malloc(sizeof(meeting));
	if (d->arr == NULL)
	{
		printf("Error! Cannot create a meeting array.\n");
		return d;
	}
	return d;
}
meeting createMeeting(float bhour, float ehour, int room)
{
	meeting m = (meeting)malloc(sizeof(struct meeting));
	if (m == NULL || bhour >= ehour || bhour < 0 || ehour > 24)
	{
		printf("Error! Cannot create a meeting.\n");
		return m;
	}
	m->bhour = bhour;
	m->ehour = ehour;
	m->room = room;
	return m;
}
diary insert(diary d, meeting m)
{
	int i, j;
	if(d == NULL || d->arr == NULL || m == NULL)
	{
		printf("Error! Cannot insert meeting to diary.\n");
		return d;
	}
	if(d->amount < d->capacity)
	{
		for(i = 0; i < d->amount; i++)
		{
			if(d->arr[i] == NULL)
			{
				printf("Error! Undefined meeting in diary.\n");
				return d;
			}
			if(d->arr[i]->bhour >= m->ehour)
			{
				break;
			}
		}
		if(i == 0 || d->arr[i-1]->ehour <= m->bhour)
		{
			for(j = d->amount - 1; j >= i; j--)
			{
				d->arr[j+1] = d->arr[j];
			}
			d->arr[i] = m;
			d->amount++;
			printf("Meeting added successfully between %d and %d minutes and %d and %d minutes in room %d.\n", (int)(d->arr[i]->bhour), (60*(int)(100*(d->arr[i]->bhour)-100*(int)(d->arr[i]->bhour))/100), (int)(d->arr[i]->ehour), (60*(int)(100*(d->arr[i]->ehour)-100*(int)(d->arr[i]->ehour))/100), d->arr[i]->room);
			return d;
		}
		printf("Error! Cannot insert meeting to diary. One or more meetings are parallel to the inserted meeting.\n");
		return d;
	}
	for(i = 0; i < d->amount; i++)
	{
		if(d->arr[i] == NULL)
		{
			printf("Error! Undefined meeting in diary.\n");
			return d;
		}
		if(d->arr[i]->bhour >= m->ehour)
		{
			break;
		}
	}
	if(i == 0 || d->arr[i-1]->ehour <= m->bhour)
	{
		d->arr = (meeting*)realloc(d->arr, (2*(d->capacity))*sizeof(meeting));
		if(d->arr == NULL)
		{
			printf("Error! Cannot insert meeting to diary.\n");
			return d;
		}
		d->capacity*=2;
		for(j = d->amount - 1; j >= i; j--)
		{
			d->arr[j+1] = d->arr[j];
		}
		d->arr[i] = m;
		d->amount++;
		printf("Meeting added successfully between %d and %d minutes and %d and %d minutes in room %d.\n", (int)(d->arr[i]->bhour), (60*(int)(100*(d->arr[i]->bhour)-100*(int)(d->arr[i]->bhour))/100), (int)(d->arr[i]->ehour), (60*(int)(100*(d->arr[i]->ehour)-100*(int)(d->arr[i]->ehour))/100), d->arr[i]->room);
		return d;
	}
	printf("Error! Cannot insert meeting to diary. One or more meetings are parallel to the inserted meeting.\n");
	return d;
}
int findIndex(diary d, float beginHour)
{
	int i = ((d->amount)/2)-1;
	int l = 0;
	int r = d->amount - 1;
	if(d == NULL || d->arr == NULL || beginHour > 24 || beginHour < 0)
	{
		printf("Error! Cannot find meeting in diary.\n");
		return -1;
	}
	while(i >= 0 && i < d->amount && l<=r)
	{
		if(d->arr[i] == NULL)
		{
			printf("Error! Undefined meeting in diary.\n");
			return -1;
		}
		if(d->arr[i]->bhour > beginHour)
		{
			r = i - 1;
		}
		else if(d->arr[i]->bhour < beginHour)
		{
			l = i + 1;
		}
		else
		{
			return i;
		}
		i = (r + l)/2;
	}
	printf("Meeting not found!\n");
	return -1;
}
meeting find(diary d, float beginHour)
{
	int result = findIndex(d, beginHour);
	if(result >= 0)
	{
		return d->arr[result];
	}
	return NULL;
}
diary mremove(diary d, float beginHour)
{
	int i;
	int j;
	i = findIndex(d, beginHour);
	if(i >= 0)
	{
		free(d->arr[i]);
		for(j = i + 1; j < d->amount; j++)
		{
			d->arr[j - 1] = d->arr[j];
		}
		d->arr[j] = NULL;
		d->amount--;
	}
	return d;
}
int mprint(int i, diary d)
{
	int bmin, emin;
	if(d == NULL || d->arr == NULL)
	{
		printf("Error! Cannot print meeting.\n");
	}
	if(d->arr[i] == NULL)
	{
		printf("Illegal meeting!\n");
	}
	else
	{
		if(d->arr[i]->bhour < 10)
		{
			putchar('0');
		}
		printf("%d:",(int)d->arr[i]->bhour);
		bmin = (60*(int)(100*(d->arr[i]->bhour)-100*(int)(d->arr[i]->bhour))/100);
		if(bmin < 10)
		{
			putchar('0');
		}
		printf("%d - ", bmin);
		if(d->arr[i]->ehour < 10)
		{
			putchar('0');
		}
		printf("%d:",(int)d->arr[i]->ehour);
		emin = (60*(int)(100*(d->arr[i]->ehour)-100*(int)(d->arr[i]->ehour))/100);
		if(emin < 10)
		{
			putchar('0');
		}
		printf("%d: A meeting in room %d.\n", emin, d->arr[i]->room);
	}
	return 0;
}
int mprint2(meeting m, diary d)
{
	if(m != NULL && d != NULL)
	{
		mprint(findIndex(d, m->bhour), d);
	}
	return 0;
}
diary dprint(diary d)
{
	int i;
	if(d == NULL || d->amount == 0)
	{
		printf("No meetings to print!\n");
		return d;
	}
	for(i = 0; i < d->amount; i++)
	{
		mprint(i, d);
	}
	return d;
}
diary destroy(diary d)
{
	int i;
	if(d != NULL)
	{
		if(d->arr != NULL)
		{
			for(i = 0; i < d->amount; i++)
			{
				if(d->arr[i] != NULL)
				{
					free(d->arr[i]);
				}
			}
			free(d->arr);
		}
		free(d);
	}
	return d;
}
