#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//defin the structure of a stack
typedef struct stack{
  int* arr;
  int cap;
  int top;
}stack_t;
//initialize a stack
void stack_init(stack_t* stack, int cap){
  stack->arr = (int*)malloc(sizeof(int)*cap);
  stack->cap = cap;
  stack->top = 0;
}
//see if the stack is empty or full
void stack_if(stack_t* stack){
  if(stack->cap == stack->top){
    printf("full!\n");
  }else if(stack->top == 0){
    printf("empty!\n");
  }else{
    printf("there are %d values in it\n", stack->top);
  }
}
//push data to the stack
void stack_push(stack_t* stack, int value){
  stack->arr[stack->top++] = value;
}
//pull data out of the stack
int stack_pull(stack_t* stack){
  return stack->arr[--stack->top];
}
//free the stack
void stack_dein(stack_t* stack){
  free(stack->arr);
  stack->arr = NULL;
  stack->cap = 0;
  stack->top = 0;
}
int main(void){
  //let's store 20 values into the stack
  stack_t number;
  stack_init(&number, 20);
  for (int i = 0; i<20;i++)
    stack_push(&number, i);
  //check if the stack is full
  stack_if(&number);
  //pull out all the values
  for(;;){
    if(number.top > 0){
     int val = stack_pull(&number);
     printf("%d\n", val);
    }else{
      break;
    }
  }
  //check if the stack is empty
  stack_if(&number);
  //free the malloc
  stack_dein(&number);
  return 0;
}
