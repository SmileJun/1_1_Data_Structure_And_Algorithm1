#ifndef __MAZE_H__
#define __MAZE_H__

#define MAX_STACK_SIZE		(10000)
#define	MAX_ROW				(10 + 2)
#define	MAX_COL				(10 + 2)

#define TRUE 1
#define FALSE 0

typedef struct {
	int	rowIdx;
	int	colIdx;
	int	direction;
} element_t;

typedef struct {
	int	vert;
	int	horiz;
} direction_t;

enum {
	NORTH = 0, NORTH_EAST, EAST, SOUTH_EAST, SOUTH, SOUTH_WEST, WEST, NORTH_WEST
};

#endif