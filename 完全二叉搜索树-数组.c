#include<stdio.h>
#include<stdlib.h>

void ReadData(int* data, int num);
int compare(const void* a, const void* b);
void solve(int* data, int num, int l, int r, int* root, int rt);
int getleng(int num);
void Print(int* root, int num);
int main()
{
	int num;
	int* data;
	int* root;

	scanf("%d", &num);
	data = (int*)malloc(sizeof(int) * num);
	root = (int*)malloc(sizeof(int) * num);
	ReadData(data, num);
	solve(data, num, 0, num - 1, root, 0);
	Print(root, num);
	free(data);
	free(root);

	return 0;
}

void ReadData(int* data, int num)
{
	int i = 0;
	for (i = 0; i < num; i++) {
		scanf("%d", &data[i]);
	}
	qsort(data, num, sizeof(int), compare);
}

int compare(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

void solve(int* data, int num, int l, int r, int* root, int rt)
{
	int length = 0;
	int Left, Right;
	if (num == 0) return;
	if (num == 1) root[rt] = data[l];
	else {
		length = getleng(num);
		root[rt] = data[l + length];
		Left = 2 * rt + 1;
		Right = Left + 1;
		solve(data, length, l, l + length - 1, root, Left);
		solve(data, num - length - 1, l + length + 1, r, root, Right);
	}
}

int getleng(int num)
{
	int i;
	int sum = 1;
	int x = 0;
	for (i = -1; sum - 1 < num; i++) {
		sum *= 2;
	}
	sum /= 2;
	x = num + 1 - sum;
	x = x < sum / 2 ? x : sum / 2;
	return sum / 2 - 1 + x;
}

void Print(int* root, int num)
{
	int i, flag = 0;
	for (i = 0; i < num; i++) {
		if (!flag)flag = 1;
		else printf(" ");
		printf("%d", root[i]);
	}
	printf("\n");
}
