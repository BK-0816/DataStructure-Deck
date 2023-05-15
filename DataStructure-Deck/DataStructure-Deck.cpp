#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DEQUEUE_MAX_SIZE 100

typedef char element;

typedef struct {
	element Dequeue[DEQUEUE_MAX_SIZE];
	int front, rear;
} Dequeuetype;

void init(Dequeuetype* q) {
	q->front = q->rear = 0;
	return;
}

bool is_full(Dequeuetype* q) {
	return ((q->rear + 1) % DEQUEUE_MAX_SIZE == q->front);
}

bool is_empty(Dequeuetype* q) {
	return q->front == q->rear;
}

void push_back(Dequeuetype* q, element item) {
	if (!is_full(q)) {
		q->rear = (q->rear + 1) % DEQUEUE_MAX_SIZE;
		q->Dequeue[q->rear] = item;
	}
	else {
		fprintf(stderr, "full!.\n");
		exit(1);
	}
	return;
}

void push_front(Dequeuetype* q, element item) {
	if (is_full(q)) {
		fprintf(stderr, "full!.\n");
		exit(1);
	}
	else {
		q->Dequeue[q->front] = item;
		q->front = (q->front - 1) % DEQUEUE_MAX_SIZE;
	}
}

element pop_front(Dequeuetype* q) {
	if (is_empty(q)) {
		fprintf(stderr, "empty!.\n");
		exit(1);
	}
	else {
		q->front = (q->front + 1) % DEQUEUE_MAX_SIZE;
		return q->Dequeue[q->front];
	}
}
element pop_back(Dequeuetype* q) {
	if (is_empty(q)) {
		fprintf(stderr, "empty!.\n");
		exit(1);
	}
	else {
		element temp = q->Dequeue[q->rear];
		q->rear = (q->rear - 1) % DEQUEUE_MAX_SIZE;
		return temp;
	}
}

void check_pelindrome(char I[]) {
	Dequeuetype q;
	init(&q);
	int i = 0, j = 0;
	while (I[i] != '\0') {
		if ('a' <= I[i] && I[i] <= 'z') {
			push_back(&q, I[i]);
			j++;
		}
		else if ('A' <= I[i] && I[i] <= 'Z') {
			push_back(&q, I[i] - ('A' - 'a'));
			j++;
		}
		i++;
	}
	while (!(j == 0 || j == 1)) {
		if (pop_front(&q) != pop_back(&q)) {
			printf("%s",I);
			printf(" is not a palindrome\n");
			return;
		}
		j -= 2;
	}
	printf("%s", I);
	printf(" is a palindrome\n");
	return;
}


int main(void) {
    char input[100];
    while (1) {
        printf("Enter a string (or input 'exit'): ");
		scanf_s("%s", input, (unsigned int)_countof(input));
        if (strcmp(input, "exit") == 0) {
            printf("Program exit.\n");
            break;
        }
        check_pelindrome(input);
    }
    return 0;
}