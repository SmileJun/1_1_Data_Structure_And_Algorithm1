#ifndef __SPARSE_MAT_H__
#define __SPARSE_MAT_H__

typedef struct sparse_matrix
{
	int rowIdx;
	int colIdx;
	int value;
} sparse_matrix_t;

void transpose(const sparse_matrix_t a[], sparse_matrix_t b[]);
void fastTranspose(const sparse_matrix_t a[], sparse_matrix_t b[]);

int findEndIdxWithEqualRowIdx(const sparse_matrix_t *matrix, int startEleIdx);
void sparseMatMultiplication(const sparse_matrix_t *A, const sparse_matrix_t *B, sparse_matrix_t *C);
// 입력 A, B를 이용해서 Multiplication 결과를 C에 저장

int vectorInnerProduct(const sparse_matrix_t *A, int startOfA, int endOfA,
	const sparse_matrix_t *B, int startOfB, int endOfB);
void showSparseMatrix(const sparse_matrix_t []);

#endif