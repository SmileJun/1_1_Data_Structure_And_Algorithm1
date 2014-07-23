#ifndef __SPARSE_TRANS_ONEARR_H__
#define __SPARSE_TRANS_ONEARR_H__

typedef struct sparse_matrix
{
	int rowIdx;
	int colIdx;
	int value;
} sparse_matrix_t;

void fastTransposeWithOneArr(const sparse_matrix_t a[], sparse_matrix_t b[]);
void showSparseMatrix(const sparse_matrix_t []);

#endif