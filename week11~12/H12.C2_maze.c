/*
	�ۼ���: �ո���
	�ۼ���: 2014.06.17
	����: maze findPath() �Լ� ����
*/

#include <stdio.h>
#include <stdlib.h>
#include "H12.C2_maze.h"

// stack�� ���� �迭 ����
static	element_t	*stack;
static	int			top = -1;
static	int			capacity;

// �Ա�, �ⱸ
static element_t	entryPos;
static element_t	exitPos;

// ������ ���� ���� �迭 ����
static direction_t	offset[8];

// �̷� ���� ���� ���� maze �ֱ�ȭ
static	int		maze[MAX_ROW][MAX_COL] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, // 0��° row
		{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, // 1��° row.. [1][1]�� �Ա�
		{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, // 2��° row
		{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1 },
		{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 }, // [ROW_MAX-1][COL_MAX-1]�� �ⱸ
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } // 11��° row
};

// �湮�� �� ǥ���ϴ� 2���� �迭 �ʱ�ȭ
static int	visitMark[MAX_ROW][MAX_COL];

// �����̴� ���⿡ ���� ��ġ�� ������ ����
static void	setDirection()
{
	offset[NORTH].vert = -1;
	offset[NORTH].horiz = 0;

	offset[NORTH_EAST].vert = -1;
	offset[NORTH_EAST].horiz = 1;

	offset[EAST].vert = 0;
	offset[EAST].horiz = 1;

	offset[SOUTH_EAST].vert = 1;
	offset[SOUTH_EAST].horiz = 1;

	offset[SOUTH].vert = 1;
	offset[SOUTH].horiz = 0;

	offset[SOUTH_WEST].vert = 1;
	offset[SOUTH_WEST].horiz = -1;

	offset[WEST].vert = 0;
	offset[WEST].horiz = -1;

	offset[NORTH_WEST].vert = -1;
	offset[NORTH_WEST].horiz = -1;
}

/*
	�湮�� ǥ�� �����ϴ� 2���� �迭 �ʱ�ȭ
*/
void	resetMark()
{
	int	rowIdx, colIdx;

	for (rowIdx = 0; rowIdx < MAX_ROW; rowIdx++) {
		for (colIdx = 0; colIdx < MAX_ROW; colIdx++) {
			visitMark[rowIdx][colIdx] = 0;
		}
	}
}

/*
	�̷� ���� ��� �Լ�
*/
static void	printMaze()
{
	int	rowIdx, colIdx;

	for (rowIdx = 0; rowIdx < MAX_ROW; rowIdx++) {
		for (colIdx = 0; colIdx < MAX_COL; colIdx++) {
			printf("%1d, ", maze[rowIdx][colIdx]);
		}
		printf("\n");
	}
}

/*
	�湮�� ��ġ ��� �Լ�
*/
static void	printMark()
{
	int	rowIdx, colIdx;

	for (rowIdx = 0; rowIdx < MAX_ROW; rowIdx++) {
		for (colIdx = 0; colIdx < MAX_COL; colIdx++) {
			printf("%1d, ", visitMark[rowIdx][colIdx]);
		}
		printf("\n");
	}
}

/*
	���� �Լ�
*/
static int	createStack(int initialCapacity)
{
	stack = (element_t *)malloc(sizeof(element_t)*initialCapacity);

	if (!stack)
		return -1;

	capacity = initialCapacity;

	return 0;
}

static void push(element_t	elem)
{
	if (top >= MAX_STACK_SIZE - 1) {
		stack = (element_t *)realloc(stack, sizeof(element_t) * 2 * capacity);
		capacity *= 2;
	}
	
	stack[++top] = elem;
}

static element_t pop()
{
	if (top < 0) {
		element_t element;
		element.direction = 8;

		return element;
	}

	return stack[top--];
}

static int	isEmpty()
{
	if (top < 0)
		return TRUE;
	else
		return FALSE;
}


/*
	�Ա��� �ⱸ ��ġ�� ����
*/
static void	createMaze()
{
	entryPos.rowIdx = 1;
	entryPos.colIdx = 1;

	exitPos.rowIdx = MAX_ROW - 2;
	exitPos.colIdx = MAX_COL - 2;

	resetMark();
	setDirection();

	createStack(MAX_STACK_SIZE);
}

/*
	��� ã�� �Լ�
*/
void	findPath()
{
	element_t	pos;
	element_t	nextPos;
	int			pathFound;

	// �ʱ�ȭ
	// ���ÿ� �Ա����� �������� �̵��� ���ʶ�� ������ �����ϴ� element�� push
	// ù ��° �湮�� ��ġ�� ���ÿ� ����
	pos.rowIdx = entryPos.rowIdx;
	pos.colIdx = entryPos.colIdx;
	pos.direction = NORTH;

	push(pos);

	// �Ա��� �̹� �湮�� ���̹Ƿ� 1�� ǥ��
	visitMark[pos.rowIdx][pos.colIdx] = 1;

	// ��θ� ã�Ҵ��� ���θ� �����ϴ� ������ 0���� �ʱ�ȭ
	pathFound = 0;
	// stack�� empty�� �ƴϰ� ��θ� ���� �� ã�� ���¶�� ������ ��� ����. �� ���� �ȿ��� �Ʒ� ���� ����.
	while (!isEmpty() && !pathFound) {
		// �������� ��ġ �� �����ߴ� ���� Ȯ�� --> pop()���� ���� �� Ȯ��
		pos = pop();
		// ����� ��ġ���� �� �� �ִ� ������ �� �̻� ���� �ǰų� �ⱸ�� ã�� ������ �Ʒ� ���� ����
		// ��, �� �� �ִµ����� ������ ���鼭 ��~�� �����Ѵ�.
		while (pos.direction < 8 && !pathFound) {
			//
			//                         �ڵ带 ä�� �ڸ� (�ڵ� ���� 1�� �ڵ� ���� 2�� ä��)
			//                         �Ʒ��� �ּ� ������ �ڵ�� ������
			//

			// �̵��� ��ġ�� ����
			//    stack���� pop�ؼ� ���� pos�� �̿��ؼ� �̵��� ��ġ�� �ӽ÷� �����Ѵ�.
			nextPos.colIdx = pos.colIdx + offset[pos.direction].horiz;
			nextPos.rowIdx = pos.rowIdx + offset[pos.direction].vert;

			// �̵��� ��ġ�� ������ �������� �Ʒ� ������ �����ϴµ�
			// �� ���� ��찡 ���� �� �ִ�.
			//    1. nextPos�� �ⱸ�� ���
			//         ���� ��ġ�� stack�� push�Ѵ�. stack�� �ִ� ������ �̿��ؼ� �Ա����� �ⱸ������ ��θ� ����� �� ����ϱ� ���ؼ��̴�.
			//         
			//         ��θ� ã�����Ƿ� �̸� ǥ���ϴ� ������ 1�� �����Ѵ�.
			//
			//    2. nextPos���� �̵��� �� �ִ� ���
			//         �� ��쿡�� �� �� �ִµ����� ��~�� ���� ��쿡 �ش�ȴ�.
			//         ���� ���� �湮�� ������ 1������Ų �� pos�� stack�� push�Ѵ�.
			//         �ֳ��ϸ�, ���� �������� ���ٰ� ��θ� ��ã���� ���� ��ġ���� ���� �� �湮�� ������ �����ϱ� ���ؼ��̴�.
			//
			//         visitMark �迭���� nextPos�� �ش��ϴ� ��ġ�� �ش��ϴ� ������ ���� 1�� �����Ѵ�.
			//         ��, �湮�����Ƿ� ���� ������ �湮���� ����� ǥ����.
			//
			//         ���� ��ġ, �� pos�� �����Ѵ�. � ������? nextPos����. �׸���, nextPos���� ó�� ������ ������ �������� �����Ѵ�.
			//
			//    3. nextPos�� �̵��� �� ��� pos(���� ��ġ)���� �̵��� ������ 1��ŭ ������Ű�� ��� 
			//         ���⿡�� �̵� ������ ��� ������Ű�µ� �� �̻� Ȯ���� ������ ������ ������ ���� "pos.direction < 8"�� ���ؼ� ������ ���������� �ȴ�.
			//         �� ��Ȳ�� ���� ��ġ���� �� �̻� ã�� ������ �����Ƿ�
			//         ���� ���ÿ� ����� �� ������ ��ġ�� ���� �� �ڸ����� �̵��� ���� ������ ã�ƾ� �Ѵٴ� ���� �ǹ��Ѵ�.

			if (nextPos.colIdx == exitPos.colIdx && nextPos.rowIdx == exitPos.rowIdx)
			{
				push(pos);
				pathFound = TRUE;
			}
			else if (maze[nextPos.rowIdx][nextPos.colIdx] == 0 && visitMark[nextPos.rowIdx][nextPos.colIdx] == 0)
			{
				pos.direction++;
				push(pos);

				visitMark[nextPos.rowIdx][nextPos.colIdx] = 1;

				pos.rowIdx = nextPos.rowIdx;
				pos.colIdx = nextPos.colIdx;
				pos.direction = NORTH;
			}
			else pos.direction++;
		}
		// �� �ڸ��� ���� �� pathFound�� 0�̶�� �� �̻� ������ �� �� ���� ���¶�� �ǹ��̴�.
		// ����, ���� stack�� top�� �ִ� pos�� pop�ؼ� Ȯ���� ���ƾ� �Ѵ�.
		// Ȯ���ϴ� �۾��� �� while-loop�� ���� �� ��ܿ��� �̷������.
	}

	// ã������ ��� ���
	// �� ã������ ��� ���ٴ� ���

	if (pathFound) {
#if 1
		int	i;

		for (i = 0; i < top; i++) {
			printf("[%d, %d]���� %d ����\n", stack[i].rowIdx, stack[i].colIdx, --stack[i].direction);
		}

		// i == top�� ���
		printf("[%d, %d]���� %d ����\n", stack[i].rowIdx, stack[i].colIdx, stack[i].direction);


		printf("[%d, %d] <-- �ⱸ\n", exitPos.rowIdx, exitPos.colIdx);
#else
		// �������� ���
		printf("[%d, %d] <-- �ⱸ\n", exitPos.rowIdx, exitPos.colIdx);
		while (!isEmpty()) {
			pos = pop();
			printf("[%d, %d]���� %d ����\n", pos.rowIdx, pos.colIdx, pos.direction);
		}
#endif
	}
	else
		printf("��ΰ� ����\n");
}

void solve_maze()
{
	createMaze();

	resetMark(); // ��Ʈ������ ��� ���Ҹ� 0���� �ʱ�ȭ

	printf("--------------- �湮 ���� ǥ�� ----------\n");
	printMark();

	printf("--------------- �̷� ----------------\n");
	printMaze();

	// ��� ã��
	findPath();
}

int main(void)
{
	solve_maze();
	return 0;
}