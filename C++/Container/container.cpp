#include "tcontainer_t.h"
#include <vector>
#include <list>
#include <iostream>

bool Compare(int* a, int* b)
{
	return *a == *b;
}
bool Compare(float* a, float* b)
{
	return *a == *b;
}
int main()
{
	cout << "Ints vector from 1, 2, 3, 4, 5:\n";
	TContainer_t<int, vector<int*> > c;
	cout << "Is empty before initialization? " << c.isEmpty() << "\n";
	int arr[5] = {1, 2, 3, 4, 5};
	for(int i = 0; i < 5; i++)
	{
		c.insertToEnd(arr[i]);
	}
	cout << "Is empty after initialization? " << c.isEmpty() << " ";
	cout << "has " << c.numOfElements() << " elements.\n";
	cout << "The vector is:\n";
	for(int i = 0; i < 5; i++)
	{
		cout << c[i] << " ";
	}
	cout << "\n";
	cout << "First is: " << c.getFirst() << "\n";
	cout << "Last is: " << c.getLast() << "\n";
	int x = 3;
	cout << "Trying to find 3... " << c.findElement(x, &Compare) << '\n';
	int y = 6;
	cout << "Trying to find 6... " << c.findElement(y, &Compare) << '\n';
	cout << "Changing 3 to 8...\n";
	c.findElement(x, &Compare) = 8;
	for(int i = 0; i < 5; i++)
	{
		cout << c[i] << " ";
	}
	cout << "\n";
	cout << "Removing 8...\n";
	x = 8;
	cout << c.removeElement(x, &Compare) << '\n';
	x = 7;
	cout << "Trying to remove 7...\n";
	cout << c.removeElement(x, &Compare) << '\n';
	cout << "Trying to delete 7...\n";
	c.deleteElement(x, &Compare);
	for(int i = 0; i < 4; i++)
	{
		cout << c[i] << " ";
	}
	cout << "\n";
	cout << "Removing all elements. Their array looks like:\n";
	int** arr2 = c.removeAllElements();
	for(int i = 0; i < 4; i++)
	{
		cout << *arr2[i] << " ";
	}
	cout << "\n";
	cout << "Is empty after remove all? " << c.isEmpty() << "\n";
	cout << "Num of elements is " << c.numOfElements() << "\n\n";
	cout << "Floats list:\n";
	TContainer_t<float, list<float*> > c2;
	cout << "Is empty before initialization? " << c2.isEmpty() << "\n";
	float arr3[5] = {1.5, 2.5, 3.5, 4.5, 5.5};
	for(int i = 0; i < 5; i++)
	{
		c2.insertToEnd(arr3[i]);
	}
	cout << "Is empty after initialization? " << c2.isEmpty() << " ";
	cout << "has " << c2.numOfElements() << " elements.\n";
	cout << "The list is:\n";
	for(int i = 0; i < 5; i++)
	{
		cout << c2[i] << " ";
	}
	cout << "\n";
	cout << "First is: " << c2.getFirst() << "\n";
	cout << "Last is: " << c2.getLast() << "\n";
	float x2 = 3.5;
	cout << "Trying to find 3.5... " << c2.findElement(x2, &Compare) << '\n';
	float y2 = 6.5;
	cout << "Trying to find 6.5... " << c2.findElement(y2, &Compare) << '\n';
	cout << "Changing 3.5 to 8.5...\n";
	c2.findElement(x2, &Compare) = 8.5;
	for(int i = 0; i < 5; i++)
	{
		cout << c2[i] << " ";
	}
	cout << "\n";
	cout << "Deleting 8.5...\n";
	x2 = 8.5;
	c2.deleteElement(x2, &Compare);
	x2 = 7.5;
	cout << "Trying to remove 7.5...\n";
	cout << c2.removeElement(x2, &Compare) << '\n';
	cout << "Trying to delete 7.5...\n";
	c2.deleteElement(x2, &Compare);
	for(int i = 0; i < 4; i++)
	{
		cout << c2[i] << " ";
	}
	cout << "\n";
	x2 = 2.5;
	cout << "Trying to delete 2.5...\n";
	c2.deleteElement(x2, &Compare);
	for(int i = 0; i < 4; i++)
	{
		cout << c2[i] << " ";
	}
	cout << "\n";
	cout << "Invalid index is in purpose to check an index out of bounds exception...\n";
	cout << "Deleting all elements...:\n";
	c2.deleteAllElements();
	cout << "Is empty after delete all? " << c2.isEmpty() << "\n";
	cout << "Num of elements is " << c2.numOfElements() << "\n";
	exit(0);
	return 0;
}