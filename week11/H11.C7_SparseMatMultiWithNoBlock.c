/*
��� ������ �̸� ������� �ʴ� ������� Sparse matrix ���� ����
�����̵� 65 ~ 70�� boundary conditions�� �˻��ϴ� ��� ����
*/

int main(void)
{
	return 0;
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