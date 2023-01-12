#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern void recur(const char* pa);
extern void my_strcpy(char*pa, const char* pb);
extern void reverse2(char**pb);
void swap(int*a, int*b){
  int c = *a;
  *a = *b;
  *b = c;
}
void selectionSort(int arr[], int n)
{
    int i, min_idx;
 
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
      min_idx = i;
      for (int j = i+1;j<n;j++){
        if(arr[min_idx]>arr[j])
          min_idx = j;
      }
        // Swap the found minimum element with the first element
      if (arr[min_idx]<arr[i])    
       swap(&arr[min_idx], &arr[i]);
    }
}
typedef struct node{
  char letter;
  struct node* next;
}node_t;
int main(void){
  char output[14];
  int array[] = {13,12,11,10,9,8,7,6,5,4,3,2,1};
  char input[]="Hello World!\n";
  selectionSort(array, strlen(input));
  if(array[0] != 1){
    fprintf(stderr, "Sorting failed!\n");
    return -1;
  }
  char input2[]="\n!dlroW olleH";
  char* input3 ="\n!dlroW olleH";
  node_t* head = (node_t*)malloc(sizeof(node_t));
  node_t* begin = head;
  for (int i = 0; i<strlen(input2);i++){
      begin->letter = input[i];
      begin->next = (node_t*)malloc(sizeof(node_t));
      begin = begin->next;
  }
  begin->next = NULL;
  if(0){
    recur("\n!dlroW olleH");
  }
  int judge;
  switch(judge = 100>0?-1:1){
    case(-1):
      {goto oh;break;}
    default:{
      fprintf(stderr, "Error!\n");
    }
  }
oh:
  //my_strcpy(output, input);
  //printf("%s", output);
  //reverse2(&input3);
  //printf("%s", input3);
  for(node_t* pnew = head; pnew->next != NULL; pnew = pnew->next){
    printf("%c", pnew->letter);
  }
  return 0;
}
void recur(const char* pa){
  if(*pa){
    recur(pa+1);
    printf("%c",*pa);
  }
  return;
}
void my_strcpy(char*pa, const char*pb){
  while(*pb != '\0'){
    *pa = *pb;
    pa++;
    pb+=1;
  }
  *pa = '\0';
}
void reverse(char*ptr){
  char dest[strlen(ptr)-1];
  int i = 0;
  for(i = 0;i<strlen(ptr);i++){
    dest[i] = *(ptr+strlen(ptr)-1-i);
  }
  dest[i] = '\0';
  strcpy(ptr, dest);
}
void reverse2(char**pb){
  char* pa = (char*)malloc(sizeof(char)*strlen(*pb));
  for (int i =0;i<strlen(*pb);i++)
    *(pa+i) = *(*pb + strlen(*pb)-1-i);
  pa[strlen(*pb)] = '\0';
  *pb = pa;
}
//I spent roughly one hour on this. This includes three c libraries, linked list, recursive function, pointers, dynamic memory, for loops, goto and sorting mechanism
