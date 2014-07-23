/*
	작성자: 손명준
	작성일: 2014.06.17
	설명: maze findPath() 함수 구현
*/

#include <stdio.h>
#include <stdlib.h>
#include "H12.C2_maze.h"

// stack을 위한 배열 선언
static	element_t	*stack;
static	int			top = -1;
static	int			capacity;

// 입구, 출구
static element_t	entryPos;
static element_t	exitPos;

// 움직일 방향 저장 배열 선언
static direction_t	offset[8];

// 미로 정보 저장 변수 maze 최기화
static	int		maze[MAX_ROW][MAX_COL] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, // 0번째 row
		{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, // 1번째 row.. [1][1]이 입구
		{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, // 2번째 row
		{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1 },
		{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 }, // [ROW_MAX-1][COL_MAX-1]가 출구
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } // 11번째 row
};

// 방문한 곳 표시하는 2차원 배열 초기화
static int	visitMark[MAX_ROW][MAX_COL];

// 움직이는 방향에 따른 위치값 변동량 저장
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
	방문한 표시 저장하는 2차원 배열 초기화
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
	미로 정보 출력 함수
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
	방문한 위치 출력 함수
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
	스택 함수
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
	입구와 출구 위치를 지정
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
	경로 찾는 함수
*/
void	findPath()
{
	element_t	pos;
	element_t	nextPos;
	int			pathFound;

	// 초기화
	// 스택에 입구에서 북쪽으로 이동할 차례라는 정보를 저장하는 element를 push
	// 첫 번째 방문한 위치를 스택에 저장
	pos.rowIdx = entryPos.rowIdx;
	pos.colIdx = entryPos.colIdx;
	pos.direction = NORTH;

	push(pos);

	// 입구는 이미 방문한 곳이므로 1로 표시
	visitMark[pos.rowIdx][pos.colIdx] = 1;

	// 경로를 찾았는지 여부를 저장하는 변수를 0으로 초기화
	pathFound = 0;
	// stack이 empty가 아니고 경로를 아직 못 찾은 상태라면 루프를 계속 수행. 매 루프 안에서 아래 사항 수행.
	while (!isEmpty() && !pathFound) {
		// 마지막의 위치 및 진행했던 방향 확인 --> pop()으로 추출 후 확인
		pos = pop();
		// 추출된 위치에서 갈 수 있는 방향이 더 이상 없게 되거나 출구를 찾을 때까지 아래 루프 수행
		// 즉, 갈 수 있는데까지 루프를 돌면서 쭈~욱 진행한다.
		while (pos.direction < 8 && !pathFound) {
			//
			//                         코드를 채울 자리 (코드 조각 1과 코드 조각 2를 채움)
			//                         아래의 주석 내용을 코드로 변경함
			//

			// 이동할 위치를 저장
			//    stack에서 pop해서 얻은 pos을 이용해서 이동할 위치를 임시로 저장한다.
			nextPos.colIdx = pos.colIdx + offset[pos.direction].horiz;
			nextPos.rowIdx = pos.rowIdx + offset[pos.direction].vert;

			// 이동할 위치를 저장한 다음에는 아래 과정을 수행하는데
			// 세 가지 경우가 있을 수 있다.
			//    1. nextPos가 출구인 경우
			//         현재 위치를 stack에 push한다. stack에 있는 정보를 이용해서 입구에서 출구까지의 경로를 출력할 때 사용하기 위해서이다.
			//         
			//         경로를 찾았으므로 이를 표시하는 변수를 1로 지정한다.
			//
			//    2. nextPos으로 이동할 수 있는 경우
			//         이 경우에는 갈 수 있는데까지 쭈~욱 가는 경우에 해당된다.
			//         다음 번에 방문할 방향을 1증가시킨 후 pos를 stack에 push한다.
			//         왜냐하면, 현재 방향으로 갔다가 경로를 못찾으면 현재 위치에서 다음 번 방문할 방향을 저장하기 위해서이다.
			//
			//         visitMark 배열에서 nextPos에 해당하는 위치에 해당하는 원소의 값을 1로 지정한다.
			//         즉, 방문했으므로 다음 번에는 방문하지 말라는 표시임.
			//
			//         현재 위치, 즉 pos를 갱신한다. 어떤 값으로? nextPos으로. 그리고, nextPos에서 처음 가려는 방향은 북쪽으로 지정한다.
			//
			//    3. nextPos로 이동할 수 없어서 pos(현재 위치)에서 이동할 방향을 1만큼 증가시키는 경우 
			//         여기에서 이동 방향을 계속 증가시키는데 더 이상 확인할 방향이 없으면 루프의 조건 "pos.direction < 8"에 의해서 루프를 빠져나가게 된다.
			//         이 상황은 현재 위치에서 더 이상 찾을 방향이 없으므로
			//         현재 스택에 저장된 맨 상위의 위치로 가서 그 자리에서 이동할 다음 방향을 찾아야 한다는 것을 의미한다.

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
		// 이 자리에 들어올 때 pathFound가 0이라면 더 이상 앞으로 갈 수 없는 상태라는 의미이다.
		// 따라서, 현재 stack의 top에 있는 pos를 pop해서 확인해 보아야 한다.
		// 확인하는 작업은 이 while-loop의 내부 중 상단에서 이루어진다.
	}

	// 찾았으면 결과 출력
	// 못 찾았으면 경로 없다는 출력

	if (pathFound) {
#if 1
		int	i;

		for (i = 0; i < top; i++) {
			printf("[%d, %d]에서 %d 방향\n", stack[i].rowIdx, stack[i].colIdx, --stack[i].direction);
		}

		// i == top인 경우
		printf("[%d, %d]에서 %d 방향\n", stack[i].rowIdx, stack[i].colIdx, stack[i].direction);


		printf("[%d, %d] <-- 출구\n", exitPos.rowIdx, exitPos.colIdx);
#else
		// 역순으로 출력
		printf("[%d, %d] <-- 출구\n", exitPos.rowIdx, exitPos.colIdx);
		while (!isEmpty()) {
			pos = pop();
			printf("[%d, %d]에서 %d 방향\n", pos.rowIdx, pos.colIdx, pos.direction);
		}
#endif
	}
	else
		printf("경로가 없음\n");
}

void solve_maze()
{
	createMaze();

	resetMark(); // 매트릭스의 모든 원소를 0으로 초기화

	printf("--------------- 방문 여부 표시 ----------\n");
	printMark();

	printf("--------------- 미로 ----------------\n");
	printMaze();

	// 경로 찾기
	findPath();
}

int main(void)
{
	solve_maze();
	return 0;
}