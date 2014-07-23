/*
	작성자: 손명준
	작성일: 2014.06.18
	설명: 오름차순 리스트인 list_x와 list_y를 합쳐 오름차순 리스트 list_z를 구성하는 함수 구현
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "H12.C3_Merge.h"
#define randomize() (srand((unsigned int)time(NULL)))
#define random(n) (rand() % n)
#define RAND_FACTOR_X 2 // random(RAND_FACTOR_X)형태로 호출
#define RAND_FACTOR_Y 3

int main(void)
{
	randomize();

	List list_x, list_y, list_z;
	initListXRandomly(&list_x);
	initListYRandomly(&list_y);
	printf("list_x : "); printAllNodes(&list_x);
	printf("list_y : "); printAllNodes(&list_y);

	list_z.head = mergeList(list_x.head, list_y.head);

	printf("list_z : "); printAllNodes(&list_z);

	return 0;
}

void initListXRandomly(List * list)
{
	Node * node1 = (Node*)malloc(sizeof(Node));
	Node * node2 = (Node*)malloc(sizeof(Node));
	Node * node3 = (Node*)malloc(sizeof(Node));
	Node * node4 = (Node*)malloc(sizeof(Node));
	Node * node5 = (Node*)malloc(sizeof(Node));
	Node * node6 = (Node*)malloc(sizeof(Node));

	node1->data = random(RAND_FACTOR_X);  node1->next = node2;
	node2->data = random(RAND_FACTOR_X) + RAND_FACTOR_X;  node2->next = node3;
	node3->data = random(RAND_FACTOR_X) + 2 * RAND_FACTOR_X;  node3->next = node4;
	node4->data = random(RAND_FACTOR_X) + 3 * RAND_FACTOR_X;  node4->next = node5;
	node5->data = random(RAND_FACTOR_X) + 4 * RAND_FACTOR_X;  node5->next = node6;
	node6->data = random(RAND_FACTOR_X) + 5 * RAND_FACTOR_X; node6->next = NULL;

	list->head = node1;
	list->tail = node6;
}
void initListYRandomly(List * list)
{
	Node * node1 = (Node*)malloc(sizeof(Node));
	Node * node2 = (Node*)malloc(sizeof(Node));
	Node * node3 = (Node*)malloc(sizeof(Node));
	Node * node4 = (Node*)malloc(sizeof(Node));
	Node * node5 = (Node*)malloc(sizeof(Node));
	Node * node6 = (Node*)malloc(sizeof(Node));

	node1->data = random(RAND_FACTOR_Y);  node1->next = node2;
	node2->data = random(RAND_FACTOR_Y) + RAND_FACTOR_Y;  node2->next = node3;
	node3->data = random(RAND_FACTOR_Y) + 2 * RAND_FACTOR_Y;  node3->next = node4;
	node4->data = random(RAND_FACTOR_Y) + 3 * RAND_FACTOR_Y;  node4->next = node5;
	node5->data = random(RAND_FACTOR_Y) + 4 * RAND_FACTOR_Y;  node5->next = node6;
	node6->data = random(RAND_FACTOR_Y) + 5 * RAND_FACTOR_Y; node6->next = NULL;

	list->head = node1;
}

void printAllNodes(const List * list)
{
	Node * curNode;

	if (list == NULL) return;

	curNode = list->head;
	while (curNode) {
		printf("%d ", curNode->data);

		curNode = curNode->next;
	}
	puts("");
}

Node * mergeList(Node * head1, Node * head2)
{
	int compResult = 0;
	int compCount = 0;
	int firstIsHead1 = FALSE;
	int firstIsHead2 = FALSE;

	Node * curNode1 = (Node*)NULL;
	Node * curNode2 = (Node*)NULL;
	Node * tempNextNode = (Node*)NULL;

	if (!head1 && !head2) return (Node*)NULL;
	else if (!head1) return head2;
	else if (!head2) return head1;
	else
	{
		curNode1 = head1;
		curNode2 = head2;

		while (curNode1 != NULL && curNode2 != NULL)
		{
			compResult = compareNode(curNode1, curNode2);
			
			if (compCount++ == 0)
			{
				if (compResult == 0 || compResult == 1)
					firstIsHead2 = TRUE;
				else if (compResult == -1)
					firstIsHead1 = TRUE;
			}

			if (compResult == 0 || compResult == 1) // list1의 curNode가 크거나 같은 값을 가리키는 상황일 경우
			{
				setLinkPos(&curNode2, curNode1->data); // list2의 endPos를 찾는다, 
				tempNextNode = curNode2->next;
				curNode2->next = curNode1;
				curNode2 = tempNextNode;
			}
			else if (compResult == -1) // list2의 curNode가 크거나 같은 값을 가리키는 상황일 경우
			{
				setLinkPos(&curNode1, curNode2->data); // list1의 endPos를 찾는다. list2의 값을 바탕으로
				tempNextNode = curNode1->next;
				curNode1->next = curNode2;
				curNode1 = tempNextNode;
			}
		}

		if (firstIsHead1)
			return head1;

		return head2;
	}
}

int compareNode(Node * node1, Node * node2)
{
	if (node1 == NULL || node2 == NULL) return -999;
	else
	{
		if (node1->data > node2->data)
			return 1;
		else if (node1->data == node2->data)
			return 0;
		else
			return -1;
	}
}

void setLinkPos(Node ** curNode, int compData)
{
	int findLinkPos = FALSE;

	while ((*curNode)->next != NULL && findLinkPos == FALSE)
	{
		if ((*curNode)->next->data > compData)
			findLinkPos = TRUE;
		else
			(*curNode) = (*curNode)->next;
	}
}
