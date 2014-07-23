/*
	�ۼ���: �ո���
	�ۼ���: 2014.06.14
	����: stack API �� ���ڿ� ������ �Լ� ����
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static	char	*charStack;
static	int		top;
static	int		capacity;

/*
	�Լ���: createStack
	�Ű�����: �ʱ� capacity
	���: �־��� capcity�� ũ��� stack ����
	return ��: �����ϸ� 0, �����ϸ� -1
*/
static int	createCharStack(int initialCapacity)
{
	charStack = (char *)malloc(sizeof(char)*initialCapacity);

	if (!charStack) return -1; // ���� ���� ����

	capacity = initialCapacity;
	top = -1;

	return 0;
}

/*
	�Լ���: freeStack
	�Ű�����: ����
	���: stack�� ���� �޸𸮸� ����
*/
static void	freeStack()
{
	free(charStack);
}

/*
	�Լ���: stackExtension
	�Ű�����: ����
	���: stack�� ������ �� �ִ� �뷮�� �� ��� �ø�
	return ��: ����
*/
static void	stackExtension(void)
{
	charStack = (char *)realloc(charStack, sizeof(char) * 2 * capacity);
	capacity *= 2;
}

/*
	�Լ���: isEmpty
	�Ű�����: ����
	���: stack�� ���Ұ� �� ���� ������ Ȯ��
	return ��: stack�� empty�̸� 1, �ƴϸ� 0
*/
static int	isEmpty()
{
	if (top < 0)
		return 1;
	else
		return 0;
}

/*
	�Լ���: isFull
	�Ű�����: ����
	���: stack�� �� �� �ִ��� Ȯ��
	return ��: �� á���� 1, �ƴϸ� 0
*/
static int	isFull()
{
	if (top >= capacity - 1)
		return 1;
	else
		return 0;
}

/*
	�Լ���: push
	�Ű�����
	ch: char type
	���: ch�� stack�� top�� �߰�
	return ��: ����
*/
static void	push(char ch)
{
	if (isFull())
		stackExtension();

	charStack[++top] = ch;
}

/*
	�Լ���: pop
	�Ű�����: ����
	���: stack�� �� �� ���Ҹ� �����ϰ� �ݳ���
	return ��: ���ŵ� ����
*/
static char pop()
{
	if (isEmpty())
		return (char)NULL;
	else
		return charStack[top--];
}

/*
	�Լ���: testStringReverse
	�Ű�����: ����
	���: string reverse
	��) "ABCD"�� "DCBA"�� ������ ���
	comments
	�ʱ⿡ �뷮 1�� stack ����
	10�� ���Ҹ� �ϳ��� push
	stack�� empty�� �ɶ����� pop
*/
void	testStringReverse()
{
	char	str[] = "ABCD";
	int		i;

	if (createCharStack(1) != 0) return;

	for (i = 0; i < strlen(str); i++)
		push(str[i]);

	while (!isEmpty()) printf("%c", pop());
	printf("\n");

	freeStack();
}

int main(void)
{
	testStringReverse();
	return 0;
}