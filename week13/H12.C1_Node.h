#ifndef __NODE_H__
#define __NODE_H__

typedef struct _sNode
{
	int data;
	struct _sNode * next;
} SNode;

typedef struct _dNode
{
	int data;
	struct _dNode * prev;
	struct _dNode * next;
} DNode;

#endif