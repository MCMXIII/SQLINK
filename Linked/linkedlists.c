#include <stdio.h>
#include <stdlib.h>


struct Node {
	int value;
	struct Node* next;
};

typedef struct Node node;

/*void flip(node* list)
{
	int counter = 1;
	int* objects;
	node* listScanner = list;
	if(list == NULL || list->next == NULL)
	{
		printf("Less than 2 nodes, nothing to flip...\n");
	}
	while(listScanner->next != NULL)
	{
		counter++;
		listScanner = listScanner->next;
	}
	objects = (int*)malloc(counter*sizeof(int));
	if(objects == NULL)
	{
		printf("Cannot flip list!\n");
	}
	listScanner = list;
	while(listScanner != NULL)
	{
		objects[--counter] = listScanner->value;
		listScanner = listScanner->next;
	}
	listScanner = list;
	while(listScanner != NULL)
	{
		listScanner->value = objects[counter++];
		listScanner = listScanner->next;
	}
	free(objects);
}*/
void flip(node** list)
{
	node* listHead = *list;
	node* listScanner = *list;
	node* temp;
	if(*list == NULL || (*list)->next == NULL)
	{
		printf("Less than 2 nodes, nothing to flip...\n");
		return;
	}
	listScanner = listScanner->next;
	listHead->next = NULL;
	while(listScanner->next != NULL)
	{
		temp = listScanner->next;
		listScanner->next = listHead;
		listHead = listScanner;
		listScanner = temp;
	}
	temp->next = listHead;
	listHead = temp;
	*list = listHead;
}
node* middle(node* list)
{
	int counter = 1, secondCounter = 1;
	node* listScanner = list;
	if(list == NULL)
	{
		printf("No list - no middle...\n");
		return list;
	}
	else if(list->next == NULL || list->next->next == NULL)
	{
		return list;
	}
	while(listScanner->next != NULL)
	{
		counter++;
		listScanner = listScanner->next;
	}
	listScanner = list;
	while(listScanner->next != NULL)
	{
		if(secondCounter++ == (counter/2) + (counter%2))
		{
			return listScanner;
		}
		listScanner = listScanner->next;
	}
	return NULL;
}
int checkLoop(node* list)
{
	node* listScanner = list;
	node* listScanner2 = list;
	if(list == NULL)
	{
		printf("No loops without a list...\n");	
		return 0;
	}
	else if(list->next == NULL || list->next->next == NULL)
	{
		return 0;
	}
	while(listScanner2->next != NULL && listScanner2->next->next != NULL)
	{
		listScanner = listScanner->next;
		listScanner2 = listScanner2->next->next;
		if(listScanner == listScanner2)
		{
			return 1;
		}
	}
	return 0;
}
node* findFirstCommon(node* list1, node* list2)
{
	int counter1 = 1, counter2 = 1;
	node* listScanner1 = list1;
	node* listScanner2 = list2;
	if(list1 == NULL || list2 == NULL)
	{
		printf("No common node with an empty list...\n");
		return NULL;
	}

	while(listScanner1->next != NULL && listScanner2->next != NULL)
	{
		counter1++;
		counter2++;
		listScanner1 = listScanner1->next;
		listScanner2 = listScanner2->next;
	}
	while(listScanner1->next != NULL)
	{
		counter1++;
		listScanner1 = listScanner1->next;
	}
	while(listScanner2->next != NULL)
	{
		counter2++;
		listScanner2 = listScanner2->next;
	}
	listScanner1 = list1;
	listScanner2 = list2;
	while(counter1 > counter2)
	{
		listScanner1 = listScanner1->next;
		counter1--;
	}
	while(counter1 < counter2)
	{
		listScanner2 = listScanner2->next;
		counter2--;
	}
	while(listScanner1->next != NULL && listScanner2->next != NULL)
	{
		if(listScanner1 == listScanner2)
		{
			return listScanner1;
		}
		listScanner1 = listScanner1->next;
		listScanner2 = listScanner2->next;
	}
	printf("No common nodes!\n");
	return NULL;
}
/*******************************
******Assistant Functions:******
*******************************/
void split(node* list1, node* list2)
{
	int counter1 = 1, counter2 = 1;
	node* listScanner1 = list1;
	node* listScanner2 = list2;
	if(list1 == NULL || list2 == NULL)
	{
		return;
	}

	while(listScanner1->next != NULL && listScanner2->next != NULL)
	{
		counter1++;
		counter2++;
		listScanner1 = listScanner1->next;
		listScanner2 = listScanner2->next;
	}
	while(listScanner1->next != NULL)
	{
		counter1++;
		listScanner1 = listScanner1->next;
	}
	while(listScanner2->next != NULL)
	{
		counter2++;
		listScanner2 = listScanner2->next;
	}
	listScanner1 = list1;
	listScanner2 = list2;
	while(counter1 > counter2)
	{
		listScanner1 = listScanner1->next;
		counter1--;
	}
	while(counter1 < counter2)
	{
		listScanner2 = listScanner2->next;
		counter2--;
	}
	while(listScanner1->next != NULL && listScanner2->next != NULL)
	{
		if(listScanner1->next == listScanner2->next)
		{
			listScanner2->next = NULL;
			return;
		}
		listScanner1 = listScanner1->next;
		listScanner2 = listScanner2->next;
	}
}
void printList(node* list)
{
	node* listScanner = list;
	if(list == NULL)
	{
		printf("Nothing to print...\n");
		return;
	}
	while(listScanner != NULL)
	{
		printf("%d ", listScanner->value);
		listScanner = listScanner->next;
	}
	printf("\n");
}
void freeList(node* list)
{
	node* listScanner = list;
	node* next;
	if(list == NULL)
	{
		printf("Nothing to free...\n");
		return;
	}
	if(list->next == NULL)
	{
		free(list);
		return;
	}
	while(listScanner != NULL)
	{
		next = listScanner->next;
		free(listScanner);
		listScanner = next;
	}
}
node* generateAutoList(int length, int start, int jump)
{
	int i = 0;
	node* head = (node*)malloc(sizeof(node));
	node* current = head;
	if(current == NULL)
	{
		free(head);
		return;
	}
	for(i = start; i < length; i++)
	{
		current->value = jump*(i + 1);
		if(i < length - 1)
		{
			current->next = (node*)malloc(sizeof(node));
			if(current == NULL)
			{
				freeList(head);
				return;
			}	
		}
		else
		{
			current->next = NULL;
		}
		if(current->next != NULL)
		{
			current = current->next;
		}
	}
	return head;
}
node* returnEnd(node* list)
{
	while(list->next != NULL)
	{
		list = list->next;
	}
	return list;	
}
node* returnNode(node* list, int index)
{
	int i = 1;
	while(list->next != NULL)
	{
		if(i == index)
		{
			return list;
		}
		list = list->next;
		i++;
	}
	return list;	
}
/*******************************
*********Main Function:*********
*******************************/
int main()
{
	node* head;
	node* head2;
	node* current = head;
	node* ten;
	node* output;
	head = generateAutoList(15, 0, 1);
	current = returnEnd(head);
	printList(head);
	flip(&head);
	printList(head);
	printf("%d\n", middle(head)->value);
	flip(&head);
	printf("%d\n", checkLoop(head));
	ten = returnNode(head, 10);
	current->next = ten;
	printf("%d\n", checkLoop(head));
	current->next = NULL;
	head2 = (node*)malloc(sizeof(node));
	head2 = generateAutoList(4, 0, 2);
	current = returnEnd(head2);
	current->next = ten;
	printList(head);
	printList(head2);
	printf("%d\n", findFirstCommon(head, head2)->value);
	printf("%d\n", findFirstCommon(head, head)->value);
	split(head, head2);
	output = findFirstCommon(head, head2);
	freeList(head);
	printList(head2);
	if(output != NULL)
	{
		printf("%d\n", output->value);
	}
	flip(&head2);
	printList(head2);
	freeList(head2);
	return 0;
}