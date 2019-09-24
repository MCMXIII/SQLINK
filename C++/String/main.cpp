#include "stringtype.h"
#include <stdio.h>
#include <iostream>

using namespace std;
int main()
{
	stringType s1;
	char input[100];
	int action = -1;
	printf("Enter a string:\n");
	scanf("%s", input);
	stringType s2(input);
	stringType s3(s2);
	s1=s3;
	printf("s1: ");
	s1.print();
	printf("s2: ");
	s2.print();
	printf("s3: ");
	s3.print();
	printf("There are %d strings!\n", stringType::countStrings());
	printf("s1.compare(s2)? %d, s1.compare(s3)? %d\n", s1.compare(s2), s1.compare(s3));
	printf("s1>s2? %d, s1>s3? %d, s1>=s2? %d, s1>=s3? %d\n", s1>s2, s1>s3, s1>=s2, s1>=s3);
	printf("s1<s2? %d, s1<s3? %d, s1<=s2? %d, s1<=s3? %d\n", s1<s2, s1<s3, s1<=s2, s1<=s3);
	printf("s1==s2? %d, s1==s3? %d, s1!=s2? %d, s1!=s3? %d\n", s1==s2, s1==s3, s1!=s2, s1!=s3);
	printf("s3>\"1913\"? %d, s3>=?\"1913\" %d, s3<\"1913\"? %d, s3<=\"1913\"? %d\n", s3>"1913", s3>="1913", s3<"1913", s3<="1913");
	printf("s3==\"1913\"? %d, s3!=\"1913\"? %d\n", s3=="1913", s3!="1913");
	printf("\n");
	int x;
	char c;
	unsigned int u;
	stringType s4;
	while(action != 0)
	{
		printf("1 to set s3, 2 to get s3, 3 to get s3's length, 4 to change s3 to upper case, 5 to change s3 to lower case, 6 to prepend s1 to s3, 7 to prepend a new string to s3, 8 to append s1 to s3, 9 to append a new string to s3, 10 to check if s3 contains s1, 11 to check if s3 contains an input string, 12 to print a character in a specified index of s3, 13 to change case sensitivity, 14 to change capacity, 15 to get the first index of a character in s3, 16 to get the last index of a character in s3, 17 to get a substring of s3, 0 to quit!\n");
		scanf("%d", &action);
		switch(action)
		{
			case 1:
				printf("Enter new text:\n");
				/*scanf("%s", input);*/
				cin>>s3;
				break;
			case 2:
				printf("s3 is %s.\n", s3.getString());
				break;
			case 3:
				printf("s3's length is %d.\n", s3.length());
				break;
			case 4:
				s3.toUpper();
				break;
			case 5:
				s3.toLower();
				break;
			case 6:
				s3.prepend(s1);
				break;
			case 7:
				printf("Enter new text:\n");
				scanf("%s", input);
				s3.prepend(input);
				break;
			case 8:
				s3+=s1;
				break;
			case 9:
				printf("Enter new text:\n");
				scanf("%s", input);
				s3+=input;
				break;
			case 10:
				printf("Is s1 in s3? %d\n", s3.contains(s1));
				break;
			case 11:
				printf("Enter new text:\n");
				scanf("%s", input);
				printf("Is %s in s3? %d\n", input, s3.contains(input));
				break;
			case 12:
				printf("Enter an index:\n");
				scanf("%d", &action);
				printf("s3[%d] = %c\n", action, s3[action]);
				action = 12;
				break;
			case 13:
				x = stringType::setCaseSens();
				printf("Previous case sensitivity was %d, current case sensitivity is %d!\n", x, stringType::getCaseSens());
				break;
			case 14:
				printf("Enter a new capacity:\n");
				scanf("%d", &action);
				x = stringType::setCapacity(action);
				printf("Previous capacity was %d, current capacity is %d!\n", x, stringType::getCapacity());
				action = 14;
				break;
			case 15:
				printf("Enter a character:\n");
				scanf("\n%c", &c);
				printf("The first index of %c is %d!\n", c, s3.firstIndex(c));
				break;
			case 16:
				printf("Enter a character:\n");
				scanf("\n%c", &c);
				printf("The last index of %c is %d!\n", c, s3.lastIndex(c));
				break;
			case 17:
				printf("Enter a first index:\n");
				scanf("%d", &action);
				printf("Enter a length:\n");
				scanf("%u", &u);
				s4 = s3(action, u);
				printf("%u characters long substring of s3 which starts in %d: ", u, action);
				s4.print();
				action = 17;
				break;
			default:
				break;
		}
		if(action >= 1 && action <= 17)
		{
			printf("\n");
			printf("s1: ");
			s1.print();
			printf("s2: ");
			s2.print();
			printf("s3: ");
			s3.print();
			printf("There are %d strings!\n", stringType::countStrings());
			printf("s1.compare(s2)? %d, s1.compare(s3)? %d\n", s1.compare(s2), s1.compare(s3));
			printf("s1>s2? %d, s1>s3? %d, s1>=s2? %d, s1>=s3? %d\n", s1>s2, s1>s3, s1>=s2, s1>=s3);
			printf("s1<s2? %d, s1<s3? %d, s1<=s2? %d, s1<=s3? %d\n", s1<s2, s1<s3, s1<=s2, s1<=s3);
			printf("s1==s2? %d, s1==s3? %d, s1!=s2? %d, s1!=s3? %d\n", s1==s2, s1==s3, s1!=s2, s1!=s3);
			printf("s3>\"1913\"? %d, s3>=?\"1913\" %d, s3<\"1913\"? %d, s3<=\"1913\"? %d\n", s3>"1913", s3>="1913", s3<"1913", s3<="1913");
			printf("s3==\"1913\"? %d, s3!=\"1913\"? %d\n", s3=="1913", s3!="1913");
			printf("\n");
		}
	}
	return 0;
}