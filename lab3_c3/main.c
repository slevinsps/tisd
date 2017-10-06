#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define OK 0
#define STACK_OVERFOW -1
#define STACK_UNDERFLOW -2

#define SIZE_STACK 50

typedef struct Stack {
    int *AUB;
    int *PS;
    int *ALB;
    int L;
} Stack;


int push(Stack *stack_arr, int data)
{
    int err = OK;
    stack_arr->PS += stack_arr->L;
    if (stack_arr->PS > stack_arr->ALB)
        err = STACK_OVERFOW;
    
    *(stack_arr->PS) = data;
    return err;    
}

int pop(Stack *stack_arr)
{
    int err = OK;
    stack_arr->PS -= stack_arr->L;
    if (stack_arr->PS < stack_arr->AUB)
        err = STACK_UNDERFLOW;

    return err;    
}


void print_stack(Stack *stack_arr)
{
    for (int i = 0; i <= stack_arr->PS - stack_arr->AUB; i++)
    {
        printf("%d ",*(stack_arr->AUB+i));
    }
}


int main(void)
{
    int err = OK;    
    
    Stack stack_arr;
    int arr1[SIZE_STACK];
    stack_arr.AUB = arr1;
    stack_arr.PS = arr1-1;
    stack_arr.ALB = arr1 + SIZE_STACK;
    stack_arr.L = 1;
    
    err = push(&stack_arr,7);
    err = push(&stack_arr,2);
    pop(&stack_arr);
    push(&stack_arr,8);
    push(&stack_arr,-4);
    
    print_stack(&stack_arr);
    return err;
}
