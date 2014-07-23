#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__
#include "H12.C1_Node.h"

typedef struct _sLinkedList
{
	SNode * head;
} SLinkedList;

typedef struct _dLinkedList
{
	DNode * head;
} DLinkedList;

//Singly LinkedList 관련 함수들
void initListDirectly(SLinkedList * list, int plus);
void printListWithForm(const SLinkedList * list);
void initListByInsertNodeAtFront(SLinkedList * list);
void printAllNodes(const SLinkedList * list);
void insertNodeAtFront(SLinkedList * list, SNode * node);
SNode * searchNode(const SLinkedList * list, int key);
void showfindNode(const SNode * findNode);
void insertNode(SLinkedList * list, SNode * nodeA, SNode * nodeB);
void deleteNode(SLinkedList * list, SNode * prevN, SNode * targetN);

SNode * invert_linked_list(SNode * head);
SNode * concatenate(SNode * head1, SNode * head2);

//Doubly LinkedList 관련 함수들
void initDListDirectly(DLinkedList * list);
void printDListWithForm(const DLinkedList * list);
void printAllDNodes(const DLinkedList * list);
DNode * searchDNode(DLinkedList * list, int key);
void showfindDNode(const DNode * findNode);
void insertDNode(DNode * node, DNode * newNode);
void deleteDNode(DLinkedList * list, DNode * targetDN);

#endif
