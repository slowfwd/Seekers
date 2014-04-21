#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define CAPACITY 20

typedef struct STACK{

	int array[CAPACITY];
	int tos;//top of stack
}stack;

void initStack(stack *);
int pop(stack *);
void push(stack * , int);
bool isStackEmpty(stack *);
void printStack(stack *);
