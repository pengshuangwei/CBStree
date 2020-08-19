#include<stdio.h>
#include<stdlib.h>

typedef struct Node* PtrToNode;
typedef struct TreeNode* pTree;
struct Node{ /* 队列中的结点 */
	pTree p;
	PtrToNode Next;
};
typedef PtrToNode Position;

struct QNode {
	Position Front, Rear;  /* 队列的头、尾指针 */
	int MaxSize;           /* 队列最大容量 */
};
typedef struct QNode* Queue;


struct TreeNode {
	int data;
	pTree Left;
	pTree Right;
};


void ReadData(int* data, int num);
int compare(const void* a, const void* b);
pTree solve(int* data, int num, int l, int r, pTree root);
int getleng(int num);
void Print(pTree root ,Queue Q);
void Push(Queue Q, pTree p);
int isEmpty(Queue Q);
pTree Pop(Queue Q);
int main()
{
	int num;
	int* data;
	pTree root=NULL;
	Queue Q = NULL;
	Q = (Queue)malloc(sizeof(struct QNode));
	if (!Q) {
		printf("申请失败");
		return -1;
	}
	scanf_s("%d", &num);
	Q->MaxSize = num;
	Q->Front = Q->Rear = NULL;
	data = (int*)malloc(sizeof(int) * num);
	ReadData(data, num);
	root=solve(data, num, 0, num - 1, root);
	Print(root,Q);
	free(data);
	free(Q);

	return 0;
}

void ReadData(int* data, int num)
{
	int i = 0;
	for (i = 0; i < num; i++) {
		scanf_s("%d", &data[i]);
	}
	qsort(data, num, sizeof(int), compare);
}

int compare(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

pTree solve(int* data, int num, int l, int r, pTree root)
{
	int length = 0;
	if (num == 0) return NULL;
	root = (pTree)malloc(sizeof(struct TreeNode));
	if (!root) {
		printf("申请失败");
		return NULL;
	}
	if (num == 1) {
		root->data = data[l];
		root->Left = root->Right = NULL;
		return root;
	}
	else {
		length = getleng(num);
		root->data = data[l+length];
		root->Left=solve(data, length, l, l+length - 1, root->Left);
		root->Right=solve(data, num - length - 1, l+length + 1, r, root->Right);
		return root;
	}
}

int getleng(int num)
{
	int i;
	int sum = 1;
	int x = 0;
	for (i = -1;sum-1<num; i++) {
		sum *= 2;
	}
	sum /= 2;
	x = num + 1 - sum;
	x = x < sum/2 ? x : sum/2;
	return sum / 2 - 1 + x;
}

void Print(pTree root,Queue Q)
{
	pTree cur = NULL;
	int flag = 0;

	Push(Q, root);
	while(isEmpty(Q)) {
		cur = Pop(Q);
		if (!flag)flag = 1;
		else printf(" ");
		printf("%d", cur->data);
		Push(Q,cur->Left);
		Push(Q,cur->Right);
		free(cur);
		cur = NULL;
	}


}

void Push(Queue Q, pTree p)
{
	if (p == NULL) return;
	PtrToNode pos = NULL;
	pos = (PtrToNode)malloc(sizeof(struct Node));
	if (!pos) {
		printf("申请失败");
		return;
	}
	if (!Q->Front && !Q->Rear) {
		pos->p = p;
		pos->Next = NULL;
		Q->Front=Q->Rear = pos;
	}
	else {
		pos->p = p;
		Q->Rear->Next = pos;
		pos->Next = NULL;
		Q->Rear = pos;
	}
}

int isEmpty(Queue Q)
{
	if (Q->Front == NULL && Q->Rear == NULL)
		return 0;
	else return 1;
}

pTree Pop(Queue Q)
{
	Position FrontCell=NULL;
	pTree FrontElem;

	FrontCell = Q->Front;
	if (Q->Front == Q->Rear) /* 若队列只有一个元素 */
		Q->Front = Q->Rear = NULL; /* 删除后队列置为空 */
	else
		Q->Front = Q->Front->Next;
	FrontElem = FrontCell->p;

	free(FrontCell);  /* 释放被删除结点空间  */
	return  FrontElem;
	
}
