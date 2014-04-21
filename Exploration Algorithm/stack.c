#include "stack.h"

#define btoa(isStackEmpty) ((isStackEmpty)?"true":"false")

void initStack(stack * stackHead){
	stackHead->tos =-1;
	for(int i=0;i<CAPACITY;i++){
		stackHead->array[i]= -1;
	}
}

int pop(stack * stackHead){

	int top;
	if(stackHead->tos == -1)//empty stack!
		return -1;
	top = stackHead->array[stackHead->tos];
	stackHead->array[stackHead->tos] = -1;
	stackHead->tos--;
	return top;
}

void push(stack * stackHead, int ID) {

	if(stackHead->tos == CAPACITY)
		printf("Stack full");
	else{
		++(stackHead->tos);
		stackHead->array[stackHead->tos] = ID;
	}
}

void printStack(stack * stackHead){

	printf("In print\n");
	for(int i=0; i<CAPACITY;i++){
		if(stackHead -> array[i] != -1)
		printf("Element %d: %d\n",i,stackHead->array[i]);
	}
}

bool isStackEmpty(stack * stackHead){

	if(stackHead->tos == -1)
		return true;
	return false;
}


