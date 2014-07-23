/*
 141043 손명준
 HW#11.C4
 SparseMat.c
 2014.05.18 21시 06분 최종 수정
 완료
*/

#include "H11.C4_SparseMat.h"

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
	sparseMatMultiplication(d,e,f);
	showSparseMatrix(d);
	showSparseMatrix(e);
	showSparseMatrix(f);

	return 0;
}

void transpose(const sparse_matrix_t a[], sparse_matrix_t b[])
{
	int n, aId, a_cId_val, bId;

	b[0].rowIdx = a[0].colIdx;
	b[0].colIdx = a[0].rowIdx;
	b[0].value = a[0].value;
	n = a[0].value;

	if (n > 0)
	{
		bId = 1;
		
		for (a_cId_val = 0; a_cId_val < a[0].colIdx; a_cId_val++)
		{
			for (aId = 1; aId <= n; aId++)
			{
				if (a[aId].colIdx == a_cId_val)
				{
					b[bId].rowIdx = a[aId].colIdx;
					b[bId].colIdx = a[aId].rowIdx;
					b[bId].value = a[aId].value;
					bId++;
				}
			}
		}
	}
}

void fastTranspose(const sparse_matrix_t a[], sparse_matrix_t b[])
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

		startingPos[0] = 1;
		for (i = 1; i < a[0].colIdx; i++)
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];

		for (aId = 1; aId <= numTerms; aId++)
		{
			trans_pos = startingPos[a[aId].colIdx]++;
			b[trans_pos].colIdx = a[aId].rowIdx;
			b[trans_pos].rowIdx = a[aId].colIdx;
			b[trans_pos].value = a[aId].value;
		}
	}
}

int vectorInnerProduct(const sparse_matrix_t *A, int startOfA, int endOfA,
	const sparse_matrix_t *B, int startOfB, int endOfB)
{
	int value = 0;
	int aId, bId;

	aId = startOfA;
	bId = startOfB;

	while (aId <= endOfA && bId <= endOfB) {
		if (A[aId].colIdx == B[bId].colIdx) {
			value += A[aId].value * B[bId].value;
			aId++;
			bId++;
		}
		else if (A[aId].colIdx < B[bId].colIdx) aId++;
		else bId++;
	}

	return value;
}

void sparseMatMultiplication(const sparse_matrix_t *A, const sparse_matrix_t *B, sparse_matrix_t *C)
{
	int result = 0; 

	int startEleIdxOfA;
	int endEleIdxOfA;
	int	startEleIdxOfBT;
	int endEleIdxOfBT;

	sparse_matrix_t BT[9] = { 0 };
	fastTranspose(B, BT);

	C[0].rowIdx = A[0].rowIdx;
	C[0].colIdx = B[0].colIdx;
	C[0].value = 0;

	if (A[0].value == 0 || B[0].value == 0)
		return;
	else
	{
		startEleIdxOfA = 1;
		do
		{
			endEleIdxOfA = findEndIdxWithEqualRowIdx(A, startEleIdxOfA);

			startEleIdxOfBT = 1;
			do
			{
				endEleIdxOfBT = findEndIdxWithEqualRowIdx(BT, startEleIdxOfBT);

				result = vectorInnerProduct(A, startEleIdxOfA, endEleIdxOfA, B, startEleIdxOfBT, endEleIdxOfBT);
				if (result != 0)
				{
					C[++C[0].value].rowIdx = A[startEleIdxOfA].rowIdx;
					C[C[0].value].colIdx = A[startEleIdxOfBT].rowIdx;
					C[C[0].value].value = result;
				}
				
				startEleIdxOfBT = endEleIdxOfBT + 1;
			} while (startEleIdxOfBT <= BT[0].value);

			startEleIdxOfA = endEleIdxOfA + 1;
		} while (startEleIdxOfA <= A[0].value);
	}
}

int findEndIdxWithEqualRowIdx(const sparse_matrix_t *matrix, int startEleIdx)
{
	int endEleIdx = startEleIdx;

	while ((endEleIdx + 1) <= matrix[0].value && matrix[endEleIdx + 1].rowIdx == matrix[startEleIdx].rowIdx)
		endEleIdx++;

	return endEleIdx;
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