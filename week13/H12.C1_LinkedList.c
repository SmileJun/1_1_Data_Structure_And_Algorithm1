/*
 141043 손명준
 HW#12.C1
 LinkedList.c
 2014.06.04 23시 52분 최종 수정
 완료
*/

#include <stdio.h>
#include <stdlib.h>
#include "H12.C1_LinkedList.h"

int main(void)
{
	SLinkedList list1;
	puts("실습 주제 (1)~(2)");
	initListDirectly(&list1, 0);
	printListWithForm(&list1);

	puts("\n실습 주제 (3)");
	printf("List1 : "); printAllNodes(&list1);

	puts("\n실습 주제 (4)");
	SLinkedList list2;
	list2.head = NULL;
	initListByInsertNodeAtFront(&list2);
	printf("List2 : "); printAllNodes(&list2);

	puts("\n실습 주제 (5)");
	SNode * findNode;
	findNode = searchNode(&list1, 30);
	showfindNode(findNode);
	findNode = searchNode(&list1, 70);
	showfindNode(findNode);

	puts("\n실습 주제 (6)~(7)");
	puts("테스트 1");
	findNode = searchNode(&list1, 40);
	SNode * newNode = (SNode*)malloc(sizeof(SNode));
	newNode->data = 45;
	insertNode(&list1, findNode, newNode);
	printf("List1 : "); printAllNodes(&list1);

	puts("테스트 2"); // NULL일 때 노드 추가
	newNode = (SNode*)malloc(sizeof(SNode));
	newNode->data = 5;
	insertNode(&list1, NULL, newNode);
	printf("List1 : "); printAllNodes(&list1);
	
	puts("\n실습 주제 (8)~(9)");
	SNode * targetN;
	SNode * delPrevNode;

	puts("테스트 1");
	delPrevNode = searchNode(&list1, 30);
	targetN = searchNode(&list1, 40);

	deleteNode(&list1, delPrevNode, findNode);
	printf("List1 : "); printAllNodes(&list1);

	puts("테스트 2");
	while(list1.head)
		deleteNode(&list1, NULL, list1.head);
	printf("List1 : "); printAllNodes(&list1);

	//list2도 사용하였으므로 지워줌
	while (list2.head)
		deleteNode(&list2, NULL, list2.head);

	puts("\n실습 주제 (10)");
	initListDirectly(&list1, 0);
	SNode * invertHead = (SNode*)NULL;
	invertHead = invert_linked_list(list1.head);
	list1.head = invertHead;
	printf("List1 : "); printAllNodes(&list1);
	
	//List1을 다시 원래 모양으로 만들기 위해 한 번 더 뒤집는다
	invertHead = invert_linked_list(list1.head);
	list1.head = invertHead;

	puts("\n실습 주제 (11)~(12)");
	SNode * concateHead = (SNode*)NULL;
	initListDirectly(&list2, 100);
	printf("List1 : "); printAllNodes(&list1);
	printf("List2 : "); printAllNodes(&list2);
	concateHead = concatenate(list1.head, list2.head);
	list1.head = concateHead;
	printf("List1 + List2 : "); printAllNodes(&list1);

	puts("\n==============================");

	puts("\n실습 주제 (13)~(14)");
	DLinkedList dList;
	initDListDirectly(&dList);
	printDListWithForm(&dList);

	puts("\n실습 주제 (15)");
	printAllDNodes(&dList);

	puts("\n실습 주제 (16)");
	DNode * findDNode;
	findDNode = searchDNode(&dList, 1);
	showfindDNode(findDNode);
	findDNode = searchDNode(&dList, 20);
	showfindDNode(findDNode);

	puts("\n실습 주제 (17)");
	findDNode = searchDNode(&dList, 16);
	DNode * newDNode = (DNode*)malloc(sizeof(DNode));
	newDNode->data = 45;
	insertDNode(findDNode, newDNode);
	printAllDNodes(&dList);

	puts("\n실습 주제 (18)");
	deleteDNode(&dList, findDNode);
	printAllDNodes(&dList);

	return 0;
}





//SLinkedList 함수들

void initListDirectly(SLinkedList * list, int plus)
{
	SNode * node1 = (SNode*)malloc(sizeof(SNode));
	SNode * node2 = (SNode*)malloc(sizeof(SNode));
	SNode * node3 = (SNode*)malloc(sizeof(SNode));
	SNode * node4 = (SNode*)malloc(sizeof(SNode));
	SNode * node5 = (SNode*)malloc(sizeof(SNode));
	SNode * node6 = (SNode*)malloc(sizeof(SNode));

	node1->data = 10 + plus;  node1->next = node2;
	node2->data = 20 + plus;  node2->next = node3;
	node3->data = 30 + plus;  node3->next = node4;
	node4->data = 40 + plus;  node4->next = node5;
	node5->data = 50 + plus;  node5->next = node6;
	node6->data = 100 + plus; node6->next = NULL;

	list->head = node1;
}

void printListWithForm(const SLinkedList * list)
{
	SNode * curNode = list->head;
	
	while (curNode != NULL)
	{
		if (curNode->next != NULL)
			printf("%d %p %d\n", curNode->data, curNode, curNode->next->data);
		else
			printf("%d %p %s\n", curNode->data, curNode, "없음");

		curNode = curNode->next;
	}
}

void printAllNodes(const SLinkedList * list)
{
	SNode * curNode;

	if (list == NULL) return;

	curNode = list->head;
	while (curNode) {
		printf("%d ", curNode->data);

		curNode = curNode->next;
	}
	puts("");
}

void initListByInsertNodeAtFront(SLinkedList * list)
{
	SNode * node1 = (SNode*)malloc(sizeof(SNode));
	SNode * node2 = (SNode*)malloc(sizeof(SNode));
	SNode * node3 = (SNode*)malloc(sizeof(SNode));
	SNode * node4 = (SNode*)malloc(sizeof(SNode));
	SNode * node5 = (SNode*)malloc(sizeof(SNode));
	SNode * node6 = (SNode*)malloc(sizeof(SNode));

	node1->data = 10;
	node2->data = 20; 
	node3->data = 30;  
	node4->data = 40;  
	node5->data = 50;  
	node6->data = 100;

	insertNodeAtFront(list, node1);
	insertNodeAtFront(list, node2);
	insertNodeAtFront(list, node3);
	insertNodeAtFront(list, node4);
	insertNodeAtFront(list, node5);
	insertNodeAtFront(list, node6);
}
void insertNodeAtFront(SLinkedList * list, SNode * node)
{
	if (list == NULL && node == NULL) return;

	if (list->head)
	{
		node->next = list->head;
		list->head = node;
	}
	else
	{
		list->head = node;
		node->next = NULL;
	}
}

SNode * searchNode(const SLinkedList * list, int key)
{
	SNode * curNode;

	if (list == NULL)
		return (SNode*)NULL;

	curNode = list->head;

	while (curNode)
	{
		if (curNode->data == key)
			return curNode;
		curNode = curNode->next;
	}

	return (SNode*)NULL;
}

void showfindNode(const SNode * findNode)
{
	if (findNode)
		printf("findNode->data : %d\n", findNode->data);
	else
		puts("findNode : NULL");
}

void insertNode(SLinkedList * list, SNode * nodeA, SNode * nodeB)
{
	if (list == NULL || nodeB == NULL)
		return;

	if (list->head == NULL)
	{
		nodeB->next = NULL;
		list->head = nodeB;
	}
	else
	{
		if (nodeA == NULL)
		{
			nodeB->next = list->head;
			list->head = nodeB;
		} 
		else
		{
			nodeB->next = nodeA->next;
			nodeA->next = nodeB;
		}
	}
}

void deleteNode(SLinkedList * list, SNode * prevN, SNode * targetN)
{
	if (list == NULL || targetN == NULL) return;

	if (prevN)
		prevN->next = targetN->next;
	else if (!prevN && targetN == list->head)
		list->head = targetN->next;

	free(targetN);
}

SNode * invert_linked_list(SNode * head)
{
	SNode * newHead = (SNode*)NULL;
	SNode * tempNode = (SNode*)NULL;
	
	while (head)
	{
		tempNode = head;
		head = head->next;
		tempNode->next = newHead;
		newHead = tempNode;
	}
	return newHead;
}

SNode * concatenate(SNode * head1, SNode * head2)
{
	SNode * curNode = (SNode*)NULL;
	
	if (!head1 && !head2) return (SNode*)NULL;
	else if (!head1) return head2;
	else if (!head2) return head1;
	else
	{
		curNode = head1;
		while (curNode->next)
			curNode = curNode->next;

		curNode->next = head2;

		return head1;
	}
}

///////////////////////////////////////////////////


//DLinkedList 함수들

void initDListDirectly(DLinkedList * list)
{
	DNode * dummyNode = (DNode*)malloc(sizeof(DNode));
	DNode * node1 = (DNode*)malloc(sizeof(DNode));
	DNode * node2 = (DNode*)malloc(sizeof(DNode));
	DNode * node3 = (DNode*)malloc(sizeof(DNode));
	DNode * node4 = (DNode*)malloc(sizeof(DNode));
	
	dummyNode->data = (int)NULL;
	dummyNode->next = node1; dummyNode->prev = node4;

	node1->data = 9;  
	node1->next = node2; node1->prev = dummyNode;

	node2->data = 16; 
	node2->next = node3; node2->prev = node1;

	node3->data = 4;  
	node3->next = node4; node3->prev = node2;

	node4->data = 1; 
	node4->next = dummyNode; node4->prev = node3;

	list->head = dummyNode;
}

void printDListWithForm(const DLinkedList * list)
{
	DNode * curNode = list->head->next;

	while (curNode->data != (int)NULL)
	{
		if (curNode->prev->data != (int)NULL && curNode->next->data != (int)NULL)
			printf("%d %p %d %p %d\n", curNode->data, curNode->prev, curNode->prev->data, curNode->next, curNode->next->data);
		else if (curNode->prev->data == (int)NULL && curNode->next->data != (int)NULL)
			printf("%d %s %s %p %d\n", curNode->data, "NULL", "없음", curNode->next, curNode->next->data);
		else if (curNode->prev->data != (int)NULL && curNode->next->data == (int)NULL)
			printf("%d %p %d %s %s\n", curNode->data, curNode->prev, curNode->prev->data, "NULL", "없음");
		else
			printf("%d %s %s %s %s\n", curNode->data, "NULL", "없음", "NULL", "없음");

		curNode = curNode->next;
	}
}

void printAllDNodes(const DLinkedList * list)
{
	DNode * curNode = list->head->next;
	while (curNode->data != (int)NULL)
	{
		printf("%d ", curNode->data);
		curNode = curNode->next;
	}
	puts("");
}

DNode * searchDNode(DLinkedList * list, int key)
{
	DNode * curNode;

	if (list == NULL)
		return (DNode*)NULL;

	curNode = list->head->next;

	while (curNode->data != (int)NULL)
	{
		if (curNode->data == key)
			return curNode;
		curNode = curNode->next;
	}

	return (DNode*)NULL;
}

void showfindDNode(const DNode * findNode)
{
	if (findNode)
		printf("findNode->data : %d\n", findNode->data);
	else
		puts("findNode : NULL");
}

void insertDNode(DNode * node, DNode * newNode)
{
	if (node == NULL || newNode == NULL) return;

	newNode->prev = node;
	newNode->next = node->next;
	node->next = newNode;
	if(newNode->next)
		newNode->next->prev = newNode;
}


void deleteDNode(DLinkedList * list, DNode * targetDN)
{
	if (list == NULL || targetDN == NULL || list->head == targetDN) return;

	if (targetDN->prev != NULL)	targetDN->prev->next = targetDN->next;
	if (targetDN->next != NULL)	targetDN->next->prev = targetDN->prev;

	free(targetDN);
}
