#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#define MAX_QUEUE_SIZE 100
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

typedef struct {
	char data[MAX_STACK_SIZE];
	int top;
}StackType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q) {
	q->front = q->rear = 0;
}

int is_empty_queue(QueueType* q) {
	return (q->front == q->rear);
}

int is_full_queue(QueueType* q) {
	return((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, element item) {
	if (is_full_queue(q)) {
		error("큐가 포화상태입니다.\n");
	}
	else {
		q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
		q->data[q->rear] = item;
	}
}

element dequeue(QueueType* q) {
	if (is_empty_queue(q)) {
		error("큐가 공백상태입니다.\n");
	}
	else {
		q->front = (q->front + 1) % MAX_QUEUE_SIZE;
		return q->data[q->front];
	}
}

void queue_print(QueueType* q) {
	int i;
	printf("-----------------------------\n");
	printf("현재 큐의 상태: ");
	if (is_empty_queue(q)) {
		error("큐가 비어있습니다.");
	}
	else {
		for (i = (q->front + 1) % MAX_QUEUE_SIZE; i != q->rear; i = (i + 1) % MAX_QUEUE_SIZE) {
			printf("%2d ", q->data[i]);
		}
		printf("%2d\n", q->data[i]);
	}
	printf("-----------------------------\n");
}

void init_stack(StackType* s) {
	s->top = -1;
}

int is_empty_stack(StackType* s) {
	return(s->top == -1);
}

int is_full_stack(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, element item) {
	if (is_full_stack(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else {
		s->top += 1;
		s->data[s->top] = item;
	}
}

element pop(StackType* s) {
	if (is_empty_stack(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		return -1;
	}
	else return s->data[(s->top)--];
}


int main(void) {
	char str1[MAX_QUEUE_SIZE];
	char str2[MAX_QUEUE_SIZE];

	QueueType queue;
	StackType stack;

	while (1) {
		int choice = 0;
		int k = 0;
		int found = 0;
		printf("1. 회문 입력\n");
		printf("2. 회문 검사\n");
		printf("3. 종료\n");
		printf("메뉴 선택: ");
		scanf("%d", &choice);
		while (getchar() != '\n');

		switch (choice) {
		case 1:
			printf("회문을 입력하세요: ");
			scanf("%[^\n]s", &str1);
			for (int i = 0; str1[i] != '\0'; i++) {
				if (str1[i] != ' ' && str1[i] != '!' && str1[i] != ',' && str1[i] != '?' && str1[i] != '\'' && str1[i] != '.' && str1[i] != '\"') {
					str2[k++] = str1[i];
				}
			}
			str2[k] = '\0';
			break;
		case 2:
			init_queue(&queue);
			init_stack(&stack);
			for (int i = 0; str2[i] != '\0'; i++) {
				enqueue(&queue, tolower(str2[i]));
				push(&stack, tolower(str2[i]));
			}
			while (!is_empty_queue(&queue)) {
				if (dequeue(&queue) != pop(&stack)) {
					printf("회문이 아닙니다.\n");
					found++;
					break;
				}
			}
			if (found == 0) {
				printf("회문입니다.\n");
			}
			break;
		case 3:
			exit(0);
		default:
			printf("잘못된 메뉴 선택\n");
			break;
		}
	}
}