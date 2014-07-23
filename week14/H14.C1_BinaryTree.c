/*
	�ۼ���: �ո���
	�ۼ���: 2014.06.18
	����: Binary Tree �ǽ� ���� (2)~(6)
*/

#include <stdio.h>
#include <stdlib.h>
#include "H14.C1_BinaryTree.h"

int main(void)
{
	Tree * Btree = makeSampleTree();

	puts("�ǽ� ���� (2)~(3)");
	showMakeSamepleTree(Btree->root);

	puts("�ǽ� ���� (4)");
	printTreeWithInorder(Btree->root);

	puts("\n�ǽ� ���� (5)"); 
	printTreeWithPreorder(Btree->root);

	puts("\n�ǽ� ���� (6)"); 
	printTreeWithPostorder(Btree->root);

	return 0;
}


Tree * makeSampleTree()
{
	Tree * Btree = (Tree*)malloc(sizeof(Tree));

	Node * node1 = (Node*)malloc(sizeof(Node)); node1->data = '+';
	Node * node2 = (Node*)malloc(sizeof(Node)); node2->data = '*';
	Node * node3 = (Node*)malloc(sizeof(Node)); node3->data = '*';
	Node * node4 = (Node*)malloc(sizeof(Node)); node4->data = '/';
	Node * node5 = (Node*)malloc(sizeof(Node)); node5->data = 'A';
	Node * node6 = (Node*)malloc(sizeof(Node)); node6->data = 'B';
	Node * node7 = (Node*)malloc(sizeof(Node)); node7->data = 'C';
	Node * node8 = (Node*)malloc(sizeof(Node)); node8->data = 'D';
	Node * node9 = (Node*)malloc(sizeof(Node)); node9->data = 'E';
	Node * dummyNode = (Node*)malloc(sizeof(Node));

	node1->leftChild = node2;
	node1->rightChild = node9;
	node1->parent = NULL;

	node2->leftChild = node3;
	node2->rightChild = node8;
	node2->parent = node1;

	node3->leftChild = node4;
	node3->rightChild = node7;
	node3->parent = node2;

	node4->leftChild = node5;
	node4->rightChild = node6;
	node4->parent = node3;
	
	node5->leftChild = NULL;
	node5->rightChild = NULL;
	node5->parent = node4;

	node6->leftChild = NULL;
	node6->rightChild = NULL;
	node6->parent = node4;
	
	node7->leftChild = NULL;
	node7->rightChild = NULL;
	node7->parent = node3;

	node8->leftChild = NULL;
	node8->rightChild = NULL;
	node8->parent = node2;
	
	node9->leftChild = NULL;
	node9->rightChild = NULL;
	node9->parent = node1;

	Btree->root = node1;
	return Btree;
}

void showMakeSamepleTree(const Node * tree)
{
	int i;
	const Node * curNode = tree;
	
	for (i = 0; i < 4; i++) // �������� ���
	{
		printNodeInfo(curNode);
		curNode = curNode->leftChild;
	}

	printNodeInfo(curNode); // ���� ������ ��� ���
	curNode = curNode->parent->rightChild;
	printNodeInfo(curNode); // ���� �Ʒ����� ��� ����

	for(i = 0; i < 3; i++) // ������ ���� ���
	{
		curNode = curNode->parent->parent->rightChild;	
		printNodeInfo(curNode);
	}
}

void printNodeInfo(const Node * node)
{
	if (node == NULL) return;

	if (node->parent != NULL)
	{
		if (node->leftChild != NULL && node->rightChild != NULL)
			printf("%c, %p, %c, %p, %c, %p, %c\n",
			node->data, node->parent, node->parent->data, node->leftChild,
			node->leftChild->data, node->rightChild, node->rightChild->data);
		else if (node->leftChild == NULL && node->rightChild != NULL)
			printf("%c, %p, %c, %s, %s, %p, %c\n",
			node->data, node->parent, node->parent->data, "NULL",
			"����", node->rightChild, node->rightChild->data);
		else if (node->rightChild != NULL && node->rightChild == NULL)
			printf("%c, %p, %c, %p, %c, %s, %s\n",
			node->data, node->parent, node->parent->data, node->leftChild,
			node->leftChild->data, "NULL", "����");
		else
			printf("%c, %p, %c, %s, %s, %s, %s\n",
			node->data, node->parent, node->parent->data, "NULL",
			"����", "NULL", "����");
	}
	else
	{
		if (node->leftChild != NULL && node->rightChild != NULL)
			printf("%c, %s, %s, %p, %c, %p, %c\n",
			node->data, "NULL", "����", node->leftChild,
			node->leftChild->data, node->rightChild, node->rightChild->data);
		else if (node->leftChild == NULL && node->rightChild != NULL)
			printf("%c, %s, %s, %s, %s, %p, %c\n",
			node->data, "NULL", "����", "NULL",
			"����", node->rightChild, node->rightChild->data);
		else if (node->rightChild != NULL && node->rightChild == NULL)
			printf("%c, %s, %s, %p, %c, %s, %s\n",
			node->data, "NULL", "����", node->leftChild,
			node->leftChild->data, "NULL", "����");
		else
			printf("%c, %s, %s, %s, %s, %s, %s\n",
			node->data, "NULL", "����", "NULL",
			"����", "NULL", "����");
	}
}

void printTreeWithInorder(Node * node)
{
	if (node != NULL)
	{
		printTreeWithInorder(node->leftChild);
		printf("%c ", node->data);
		printTreeWithInorder(node->rightChild);
	}
}
void printTreeWithPreorder(Node * node)
{
	if (node != NULL)
	{
		printf("%c ", node->data);
		printTreeWithPreorder(node->leftChild);
		printTreeWithPreorder(node->rightChild);
	}
}
void printTreeWithPostorder(Node * node)
{
	if (node != NULL)
	{
		printTreeWithPostorder(node->leftChild);
		printTreeWithPostorder(node->rightChild);
		printf("%c ", node->data);
	}
}
