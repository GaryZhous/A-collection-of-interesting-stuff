#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>
typedef struct node{
  int val;
  struct node* next;
}node_t;
extern void add(node_t* head, int a);
extern void rm(node_t* head);
int main(void){
  node_t* head = NULL;
  head = (node_t*)malloc(sizeof(node_t));
  head->val = 10;
  for (int i = 9; i > 0; i--){
    add(head, i);
  }
  rm(head);
  node_t* current = head;
  while (current != NULL){
    printf("%d\n", current->val);
    current = current->next;
  }
  free(head);
  head = NULL;
  return 0;
}
void add(node_t* head, int a){
  node_t* current = head;
  while (current->next != NULL){
    current = current->next;
  }
  current->next = (node_t*)malloc(sizeof(node_t));
  current->next->val = a;
  current->next->next = NULL;
}

void rm(node_t* head){
  node_t* current = head;
  while (current->next->next != NULL){
    current = current->next;
  }
  current->next->val = 0;
  free(current->next);
  current->next = NULL;
}
