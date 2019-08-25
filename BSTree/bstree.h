#ifndef BSTREE_H
#define BSTREE_H

typedef struct Tree tree;
typedef void (* walkFunc)(int value);
typedef enum  {OK, AllocationError, NotFoundError, UndeclaredError} AdtStatus;
typedef enum  {Pre, In, Post} Order;

AdtStatus bstCreate(tree** t);
AdtStatus bstInsert(tree* t, int num);
AdtStatus bstSearch(tree* t, int num);
AdtStatus bstDelete(tree* t, int num);
AdtStatus bstDestroy(tree* t);
AdtStatus bstWalk(tree* t, Order order, walkFunc func);

#endif