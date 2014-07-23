#ifndef __MERGE_H__
#define __MERGE_H__

#define TRUE 1
#define FALSE 0

typedef struct _node
{
	int data;
	struct _node *next;
} Node;

typedef struct _linkedList
{
	Node * head;
	Node * tail;
	int numOfData;
} LinkedList;

typedef LinkedList List;

void initListXRandomly(List * list);
void initListYRandomly(List * list);
void printAllNodes(const List * list);

Node * mergeList(Node * head1, Node * head2);
int compareNode(Node * node1, Node * node2);
void setLinkPos(Node ** curNode, int compData);

#endif