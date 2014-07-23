#ifndef __LIST_LENGTH_H__
#define __LIST_LENGTH_H__

typedef struct _Node
{
	int data;
	struct _Node * next;
} Node;

typedef struct _LinkedList
{
	Node * head;
} LinkedList;

typedef LinkedList List;

void initListDirectly(List * list, int plus);

//returns the number of nodes in a list
int length(List * list);

#endif