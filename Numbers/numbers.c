#include <stdio.h>

int palindrome(int n)
{
	int x = n;
	int num1, num2 = 0;
	if(n < 0)
	{
		x = -n;
	}
	for(num1 = x; num1 > 0; num1/=10)
	{
		num2 *= 10;
		num2 += (num1%10);
	}
	if(x == num2)
	{
		return 1;
	}
	return 0;
}

int ascending(int n)
{
	int i, digit = 10;
	int x = n;
	if(n < 0)
	{
		x = -n;
	}
	for(i = x; i > 0; i/=10)
	{
		if(i%10 > digit)
		{
			return 0;
		}
		digit = i%10;
	}
	return 1;
}

int perfect(int n)
{
	int i, divisors = 0;
	if(n < 0)
	{
		printf("Please enter a valid number!\n");
		return -1;
	}
	else if (n == 1)
	{
		return 1;
	}
	for(i = 1; i <= n/2; i++)
	{
		if(n%i == 0)
		{
			divisors+=i;
		}
	}
	if(divisors == n)
	{
		return 1;
	}
	return 0;
}

int reverse(int n)
{
	int x = n;
	int num1, num2 = 0;
	if(n < 0)
	{
		x = -n;
	}
	for(num1 = x; num1 > 0; num1/=10)
	{
		num2 *= 10;
		num2 += (num1%10);
	}
	if(n < 0)
	{
		return num2*-1;
	}
	return num2;
}

int palindrome2(int n)/*Another version of a function to calculate if a number is a palindrome.*/
{
	return n == reverse(n) ? 1 : 0;

}

int prime(int n)
{
	int i;
	if(n < 0)
	{
		printf("Please enter a valid number!\n");
		return -1;
	}
	for(i = 2; i*i <= n; i++)
	{
		if(n%i == 0)
		{
			return 0;
		}
	}
	return 1;
}

int main()
{
	int n = 0, x;
	printf("Choose a number: ");
	scanf("%d", &n);
	if(palindrome(n) == 1)
	{
		printf("It's a palindrome!\n");
	}
	else
	{
		printf("It's not a palindrome!\n");
	}
	printf("Choose a number: ");
	scanf("%d", &n);
	if(ascending(n) == 1)
	{
		printf("It's in an ascending order!\n");
	}
	else
	{
		printf("It's not in an ascending order!\n");
	}
	printf("Choose a number: ");
	scanf("%d", &n);
	x = perfect(n);
	while(x == -1)
	{
		scanf("%d", &n);
		x = perfect(n);
	}
	if(x == 1)
	{
		printf("It's a perfect number!\n");
	}
	else
	{
		printf("It's not a perfect number!\n");
	}
	printf("Choose a number: ");
	scanf("%d", &n);
	printf("%d\n", reverse(n));
	printf("Choose a number: ");
	scanf("%d", &n);
	x = prime(n);
	while(x == -1)
	{
		scanf("%d", &n);
		x = prime(n);
	}
	if(x == 1)
	{
		printf("It's a prime number!\n");
	}
	else
	{
		printf("It's not a prime number!\n");
	}
	return 0;
}
