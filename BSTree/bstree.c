#include <stdlib.h>
#include "bstree.h"

struct bstVertex {
	int value;
	struct bstVertex* left;
	struct bstVertex* right;
};

typedef struct bstVertex vertex;

struct Tree
{
	vertex* root;
};

/**************************************
**********Assistant functions**********
**************************************/

vertex* createVertex(int num)
{
	vertex* v = (vertex*)malloc(sizeof(vertex));
	if(v == NULL)
	{
		return NULL;
	}
	v->value = num;
	v->left = NULL;
	v->right = NULL;
	return v;
}
AdtStatus wasAddedCorrectly(vertex* v)
{
	return v == NULL ? AllocationError : OK;
}
vertex* findValue(tree* t, int num)
{
	vertex* placeFinder = t->root;
	if(t == NULL || t->root == NULL)
	{
		return NULL;
	}
	while(placeFinder != NULL)
	{
		if(placeFinder->value == num)
		{
			return placeFinder;
		}
		if(placeFinder->value > num)
		{
			if(placeFinder->left == NULL)
			{
				return NULL;
			}
			placeFinder = placeFinder->left;
		}
		else
		{
			if(placeFinder->right == NULL)
			{
				return NULL;
			}
			placeFinder = placeFinder->right;
		}
	}
	return NULL;
}
vertex* findParent(tree* t, vertex* v)
{
	vertex* placeFinder = t->root;
	if(t == NULL || t->root == NULL)
	{
		return NULL;
	}
	while(placeFinder != NULL)
	{
		if(placeFinder->value >= v->value)
		{
			if(placeFinder->left == NULL)
			{
				return NULL;
			}
			if(placeFinder->left == v)
			{
				return placeFinder;
			}
			placeFinder = placeFinder->left;
		}
		else
		{
			if(placeFinder->right == NULL)
			{
				return NULL;
			}
			if(placeFinder->right == v)
			{
				return placeFinder;
			}
			placeFinder = placeFinder->right;
		}
	}
	return NULL;
}
vertex* findClosestDescendant(vertex* v)
{
	int value = v->value;
	v = v->right;
	while(v->left != NULL)
	{
		v=v->left;
	}
	return v;
}
int replaceWithSon(vertex* v, char whichSon)
{
	vertex* son;
	if(whichSon == 'r')
	{
		son = v->right;
		v->value = son->value;
		v->left = son->left;
		v->right = son->right;
		free(son);
	}
	else
	{
		son = v->left;
		v->value = son->value;
		v->left = son->left;
		v->right = son->right;
		free(son);
	}
	return 0;
}
int freeVertex(vertex* v)
{
	vertex* r;
	vertex* l;
	if(v == NULL)
	{
		return 0;
	}
	r = v->right;
	l = v->left;
	free(v);
	freeVertex(r);
	freeVertex(l);
	return 0;
}
int preOrder(vertex* v, walkFunc func)
{
	if(v == NULL)
	{
		return -1;
	}
	func(v->value);
	preOrder(v->left, func);
	preOrder(v->right, func);
}
int inOrder(vertex* v, walkFunc func)
{
	if(v == NULL)
	{
		return -1;
	}
	inOrder(v->left, func);
	func(v->value);
	inOrder(v->right, func);
}
int postOrder(vertex* v, walkFunc func)
{
	if(v == NULL)
	{
		return -1;
	}
	postOrder(v->left, func);
	postOrder(v->right, func);
	func(v->value);
}

/**************************************
*************BST functions*************
**************************************/

AdtStatus bstCreate(tree** t)
{
	if(t == NULL)
	{
		return UndeclaredError;
	}
	*t = (tree*)malloc(sizeof(tree));
	if(*t == NULL)
	{
		return AllocationError;
	}
	return 0;
}
AdtStatus bstInsert(tree* t, int num)
{
	vertex* placeFinder;
	if(t == NULL)
	{
		return UndeclaredError;
	}
	if(t->root == NULL)
	{
		t->root = createVertex(num);
		return wasAddedCorrectly(t->root);
	}
	placeFinder = t->root;
	while(placeFinder != NULL)
	{
		if(placeFinder->value >= num)
		{
			if(placeFinder->left == NULL)
			{
				placeFinder->left = createVertex(num);
				return wasAddedCorrectly(placeFinder->left);
			}
			placeFinder = placeFinder->left;
		}
		else
		{
			if(placeFinder->right == NULL)
			{
				placeFinder->right = createVertex(num);
				return wasAddedCorrectly(placeFinder->right);
			}
			placeFinder = placeFinder->right;
		}
	}
	return -1;
}
AdtStatus bstSearch(tree* t, int num)
{
	vertex* placeFinder = t->root;
	if(t == NULL || t->root == NULL)
	{
		return UndeclaredError;
	}
	while(placeFinder != NULL)
	{
		if(placeFinder->value == num)
		{
			return OK;
		}
		if(placeFinder->value > num)
		{
			if(placeFinder->left == NULL)
			{
				return NotFoundError;
			}
			placeFinder = placeFinder->left;
		}
		else
		{
			if(placeFinder->right == NULL)
			{
				return NotFoundError;
			}
			placeFinder = placeFinder->right;
		}
	}
	return NotFoundError;
}
AdtStatus bstDelete(tree* t, int num)
{
	vertex* deleted = findValue(t, num);
	vertex* parent;
	vertex* closestDescendant;
	if(t == NULL || t->root == NULL)
	{
		return UndeclaredError;
	}
	if(deleted == NULL)
	{
		return NotFoundError;
	}
	if(deleted->left == NULL && deleted->right == NULL)
	{
		if(deleted != t->root)
		{
			parent = findParent(t, deleted);
			if(deleted == parent->left)
			{
				parent->left = NULL;
			}
			else
			{
				parent->right = NULL;
			}
		}
		else
		{
			t->root = NULL;
		}
		free(deleted);
		return OK;		
	}
	if(deleted->left == NULL)
	{
		replaceWithSon(deleted, 'r');
		return OK;
	}
	if(deleted->right == NULL)
	{
		replaceWithSon(deleted, 'l');
		return OK;
	}
	closestDescendant = findClosestDescendant(deleted);
	parent = findParent(t, closestDescendant);
	deleted->value = closestDescendant->value;
	if(closestDescendant->right != NULL)
	{
		replaceWithSon(closestDescendant, 'r');
	}
	else
	{
		if(parent == deleted)
		{
			free(parent->right);
			parent->right = NULL;
		}
		else
		{
			free(parent->left);
			parent->left = NULL;
		}
	}
	return OK;
}
AdtStatus bstDestroy(tree* t)
{
	if(t == NULL)
	{
		return UndeclaredError;
	}
	if(t->root == NULL)
	{
		free(t);
		return OK;
	}
	freeVertex(t->root);
	free(t);
	return OK;
}
AdtStatus bstWalk(tree* t, Order order, walkFunc func)
{
	if(t == NULL || t->root == NULL)
	{
		return UndeclaredError;
	}
	switch(order)
	{
		case Pre:
		{
			preOrder(t->root, func);
			break;
		}
		case In:
		{
			inOrder(t->root, func);
			break;
		}
		case Post:
		{
			postOrder(t->root, func);
			break;
		}
	}
	return OK;
}