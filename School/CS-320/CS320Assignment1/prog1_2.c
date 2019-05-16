#include<stdio.h>
#include<stdlib.h>
#include"prog1_2.h"

struct stack* MakeStack(int capacity) {
    struct stack *s;
    s = (struct stack*) malloc(sizeof(struct stack));
    s->capacity = capacity;
    s->size = 0;
    s->data = (int*) malloc(s->capacity* sizeof(int));
    //free(s);
    return s;
}

void Push(struct stack *stackPtr, int data) {
    if(stackPtr->size >= stackPtr->capacity) {
        Grow(stackPtr);
    }
    stackPtr->data[stackPtr->size] = data;
    stackPtr->size++;
}

int Pop(struct stack *stackPtr) {
    if(stackPtr->size == 0) {
        return -1;    
    }
    stackPtr->size--;
    return stackPtr->data[stackPtr->size];

}

void Grow(struct stack *stackPtr) {
    stackPtr->capacity = stackPtr->capacity * 2;
}



