/*
	작성자: 손명준
	작성일: 2014.06.17
	설명: Node 수를 반환하는 length() 함수 구현
*/

#include <stdio.h>
#include "H12.C2_ListLength.h"

int main(void)
{
	List list;
	list.head = NULL;
	
	printf("Num Of Nodes : %d\n", length(&list));

	initListDirectly(&list, 0);
	
	printf("Num Of Nodes : %d\n", length(&list));
	
	return 0;
}

void initListDirectly(List * list, int plus)
{
	Node * node1 = (Node*)malloc(sizeof(Node));
	Node * node2 = (Node*)malloc(sizeof(Node));
	Node * node3 = (Node*)malloc(sizeof(Node));
	Node * node4 = (Node*)malloc(sizeof(Node));
	Node * node5 = (Node*)malloc(sizeof(Node));
	Node * node6 = (Node*)malloc(sizeof(Node));

	node1->data = 10 + plus;  node1->next = node2;
	node2->data = 20 + plus;  node2->next = node3;
	node3->data = 30 + plus;  node3->next = node4;
	node4->data = 40 + plus;  node4->next = node5;
	node5->data = 50 + plus;  node5->next = node6;
	node6->data = 100 + plus; node6->next = NULL;

	list->head = node1;
}

int length(List * list)
{
	int nodeNum = 0;

	if (list->head == NULL)
		return 0;

	Node * curNode = list->head;
	while (curNode != NULL)
	{
		nodeNum++;
		curNode = curNode->next;
	}

	return nodeNum;
}

