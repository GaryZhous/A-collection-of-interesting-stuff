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
  int* list = (int*)malloc(0);
  int init = 0;
  int load;
  int siz = 0;
  while(load != 0){
   printf("enter the size of the array:");
   scanf("%d", &load);
   siz += load;
   list = realloc(list, siz*sizeof(int));
   for (int i = 0; i<load;i++){
    printf("enter the numbers:");
    scanf("%d", &list[init++]);
    }
   }
  *size = siz;
  int* new_list = (int*)malloc(*size*sizeof(int));
  int i =0;
  int j =0;
  while (i<*size){
  int s;
  int min_idx = 0;
  for (s = 0;s<*size;s++){
    if(list[s]>list[min_idx]){
      min_idx = s;
    }
  }
  new_list[j++] = list[min_idx];
  i+=1;
  int uh = min_idx;
  for (int f =0 ;f<*size;f++){
    if(list[f]<list[uh] && list[f] != -10000){
      uh = f;
    }
  }
  new_list[j++] = list[uh];
  i+=1;
  list[min_idx] = -10000;
  list[uh] = -10000;
    }
  return new_list;
}
  new_list[j++] = min;
  i+=1;
    }
  return new_list;
}
