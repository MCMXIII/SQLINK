#include "stringtype.h"
#include <stdio.h>

int main()
{
	string s1;
	char input[100];
	int action = 0;
	printf("Enter a string:\n");
	scanf("%s", input);
	string s2(input);
	string s3(s2);
	s1=s3;
	printf("s1: ");
	s1.print();
	printf("s2: ");
	s2.print();
	printf("s3: ");
	s3.print();
	printf("s1==s2? %d, s1==s3? %d\n", s1.compare(s2), s1.compare(s3));
	while(action != 4)
	{
		printf("1 to set s3, 2 to get s3, 3 to get s3's length, 4 to quit!\n");
		scanf("%d", &action);
		switch(action)
		{
			case 1:
				printf("Enter new text:\n");
				scanf("%s", input);
				s3.setString(input);
				break;
			case 2:
				printf("%s\n", s3.getString());
				break;
			case 3:
				printf("%d\n", s3.length());
				break;
			default:
				break;
		}
		if(action >= 1 && action <= 3)
		{
			printf("s1: ");
			s1.print();
			printf("s2: ");
			s2.print();
			printf("s3: ");
			s3.print();
			printf("s1==s2? %d, s1==s3? %d\n", s1.compare(s2), s1.compare(s3));
		}
	}
	return 0;
}