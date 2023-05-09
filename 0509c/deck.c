#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_QUEUE_SIZE 20

typedef int element;
typedef struct { // ť Ÿ��
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} DequeType;
// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	
}
char* RemovePunctuations(char* str) {
	int i = 0, j = 0;
	while (str[i]) {
		if (!ispunct(str[i])) {
			str[j++] = str[i];
		}
		i++;
	}
	str[j] = '\0';
	return str;
}
// �ʱ�ȭ
void init_deque(DequeType* q)
{
	q->front = q->rear = 0;
}
// ���� ���� ���� �Լ�
int is_empty(DequeType* q)
{
	return (q->front == q->rear);
}
// ��ȭ ���� ���� �Լ�
int is_full(DequeType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// ����ť ��� �Լ�
void deque_print(DequeType* q)
{
	printf("DEQUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}
// ���� �Լ�
void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
	
	
}
// ���� �Լ�
element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
// ���� �Լ�
element get_front(DequeType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
element add_front(DequeType* q, element val)
{
	if (is_full(q))
	{
		error("ť�� ��ȭ�����Դϴ�");
		return 0;
	}
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}
element delete_rear(DequeType* q)
{
	int prev = q->rear;
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}
element get_rear(DequeType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[q->rear];
}

int palindrome_check(DequeType* q) {
	while (!is_empty(q)) {
		if (tolower(get_front(q)) != tolower(get_rear(q))) {
			return 0;
		}
		delete_front(q);
		if (!is_empty(q)) {
			delete_rear(q);
		}
	}
	return 1;
}
char* DeleteSpace(char s[])
{
	char* str = (char*)malloc(sizeof(s));
	int i, k = 0;

	for (i = 0; i < strlen(s); i++)
		if (s[i] != ' ') str[k++] = s[i];

	str[k] = '\0';
	return str;
}
int main(void)
{
	printf("�ܾ� �Է� : ");
	DequeType dq;
	char str[30];
	gets_s(str, 30);

	char str3[30];
	strcpy(str3, str);

	init_deque(&dq);
	
	char* str2 = RemovePunctuations(str);
	int len = strlen(str2);
	for (int i = 0; i < len; i++) {
		if (isalpha(str2[i])) {
			add_rear(&dq, tolower(str2[i]));
		}
	}

	if (palindrome_check(&dq)) {
		printf("%s is a palindrome\n", str3);
	}
	else {
		printf("%s is not a palindrome\n", str3);
	}
	while (1) {
		printf("�ܾ� �Է� : ");
		DequeType dq;
		char str[30];
		gets_s(str, 30);
		init_deque(&dq);

		char* str2 = RemovePunctuations(str);
		int len = strlen(str2);
		for (int i = 0; i < len; i++) {
			if (isalpha(str2[i])) {
				add_rear(&dq, tolower(str2[i]));
			}
		}

		if (palindrome_check(&dq)) {
			printf("%s is a palindrome\n", str3);
		}
		else if (strcmp(str2, "exit") == 0) {
			break;
		}
		else {
			printf("%s is not a palindrome\n", str3);
		}
	}
	return 0;
	free(str2);
	return 0;
}