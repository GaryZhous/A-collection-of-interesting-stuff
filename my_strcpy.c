#include <stdio.h>

extern void my_strcpy(char* pa, const char* pb);
int main(void){
  char a[20];
  char b[] = "Hello World!";
  my_strcpy(a, b);
  printf("%s\n", a); //it should return the value stored in array b
  return 0;
}

void my_strcpy(char* pa, const char* pb){
  while( *pb != '\0'){
    *pa = *pb;
    pa++;
    pb++;
  }
  *pa = '\0';
}
