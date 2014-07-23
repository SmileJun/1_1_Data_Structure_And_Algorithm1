#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__


typedef struct _node
{
	char data;
	struct _node * parent;
	struct _node * leftChild;
	struct _node * rightChild;
} Node;

typedef struct _binaryTree {
	Node * root;
} BinaryTree;

typedef BinaryTree Tree;

Tree * makeSampleTree();
void showMakeSamepleTree(const Node * tree);
void printNodeInfo(const Node * node);
void printTreeWithInorder(Node * node);
void printTreeWithPreorder(Node * node);
void printTreeWithPostorder(Node * node);

#endif