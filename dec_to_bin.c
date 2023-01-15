#include <stdio.h>
extern void dec_to_bin(short a);
int main(){
  short a; //2 bytes
  scanf("%hi", &a);
  printf("here's the binary code of %hi:\n", a);
  dec_to_bin(a);
  return 0;
}

void dec_to_bin(short a){
  for(int i = 15; i>-1;i--){
    int two = 1;
    if(i>0){
      for(int j=i;j>0;j--){
        two *= 2;
      }
    }
    int bit = (a%two == a)?0:1;
    a -= (a>=two)?two:0;
    printf("%d", bit);
  }
}
