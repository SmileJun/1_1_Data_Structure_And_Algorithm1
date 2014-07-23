/*
	Rewrite fastTranspose so that it uses only one array 
	rather than the two arrays required to hold rowTerms and startingPos.	
*/

/*
 141043 손명준
 HW#11.C5
 SparseMatTransposeWithOneArray.c
 2014.05.15 04시 26분 최종 수정
 완료
*/

#include "H11.C5_SparseMatTransposeWithOneArray.h"

#define MAX_ROW 6
#define MAX_COL 6
#define MAX_NUM ((6*6)+1) // (MAX_ROW * MAX_COL) + 1가 최대 갯수

#include <stdio.h>

int main(void)
{
	puts("==matrix transpose test==");
	sparse_matrix_t a[MAX_NUM] = {
		{ MAX_ROW, MAX_COL, 8 },
		{ 0, 0, 15 },
		{ 0, 3, 22 },
		{ 0, 5, -15 },
		{ 1, 1, 11 },
		{ 1, 2, 3 },
		{ 2, 3, -6 },
		{ 4, 0, 91 },
		{ 5, 2, 28 }
	};

	sparse_matrix_t b[MAX_NUM] = { 0 };
	sparse_matrix_t c[MAX_NUM] = { 0 };

	transpose(a, b);
	fastTranspose(a, c);

	showSparseMatrix(a);
	showSparseMatrix(b);
	showSparseMatrix(c);

	puts("\n==matrix multiplication test==");
	sparse_matrix_t d[MAX_NUM] = {
		{ MAX_ROW, MAX_COL, 8 },
		{ 0, 0, 15 },
		{ 0, 3, 22 },
		{ 0, 5, -15 },
		{ 1, 1, 11 },
		{ 1, 2, 3 },
		{ 2, 3, -6 },
		{ 4, 0, 91 },
		{ 5, 2, 28 }
	};
	sparse_matrix_t e[MAX_NUM] = {
		{ MAX_ROW, MAX_COL, 8 },
		{ 0, 0, 15 },
		{ 0, 4, 91 },
		{ 1, 1, 11 },
		{ 2, 1, 3 },
		{ 2, 5, 28 },
		{ 3, 0, 22 },
		{ 3, 2, -6 },
		{ 5, 0, -15 },
	};

	sparse_matrix_t f[MAX_NUM] = { 0 };
	sparseMatMultiplication(d, e, f);
	showSparseMatrix(d);
	showSparseMatrix(e);
	showSparseMatrix(f);

	return 0;
}

void fastTransposeWithOneArr(const sparse_matrix_t a[], sparse_matrix_t b[])
{
	int i, numTerms, aId, trans_pos;
	int rowTerms[MAX_COL] = { 0 };
	int startingPos[MAX_COL] = { 0 };

	numTerms = a[0].value;

	b[0].rowIdx = a[0].colIdx;
	b[0].colIdx = a[0].rowIdx;
	b[0].value = a[0].value;

	if (numTerms > 0)
	{
		for (i = 1; i <= numTerms; i++)
			rowTerms[a[i].colIdx]++;

/*
	startingPos[0] = 1;
	for (i = 1; i < a[0].colIdx; i++)
	startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
*/
		for (aId = 1; aId <= numTerms; aId++)
		{
			trans_pos = startingPos[a[aId].colIdx]++;
			b[trans_pos].colIdx = a[aId].rowIdx;
			b[trans_pos].rowIdx = a[aId].colIdx;
			b[trans_pos].value = a[aId].value;
		}
	}
}

void showSparseMatrix(const sparse_matrix_t * a)
{
	int i;
	puts("");

	printf(" id  %4s %4s %6s\n", "rid", "cid", "value");

	for (i = 0; i <= a[0].value; i++)
	{
		printf("%2d : %4d %4d %6d\n", i, a[i].rowIdx, a[i].colIdx, a[i].value);
	}
}