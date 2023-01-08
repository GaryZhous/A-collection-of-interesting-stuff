#include <stdio.h>
#include <stdlib.h>
extern int* merge(int* size);

int main(){
  int size;
  int *mergedArray = merge(&size);
  printf("Result: ");
  for (int i = 0; i < size; i ++) {
   printf("%d ", mergedArray[i]);
  }
  printf("\n");
  free(mergedArray);
  return 0;

}

int* merge(int* size){
  int count = 0;
  int list[*size];
  int* new_list = (int*)malloc(*size*sizeof(int));
  int init = 0;
  while(count<*size){
    int load;
    printf("enter the size of an array:");
    scanf("%d", &load);
    for (int i = 0;i<load;i++){
      printf("enter the numbers:");
      scanf("%d", &list[init++]);
    }
    count += load;
  }

  int j =0;
  int i =0;
  while (i<*size){
  int max = 0;
  for (;i<*size;i++){
    if(list[i]>max){
      max = list[i];
    }
  }
  new_list[j++] = max;
  i+=1;
  int min = max;
  for (;i<*size;i++){
    if(list[i]<min){
      min = list[i];
    }
  }
  new_list[j++] = min;
  i+=1;
    }
  return new_list;
}
