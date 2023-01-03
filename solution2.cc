#include <stdio.h>
#include <iostream>
int getMaximum(int*p){
  size_t n = sizeof(*p)/sizeof(p[0]);
  int max = p[0];
sussy:
  for (int i = 2; i<n;i++){
    for (int x = 1; x<p[i];x++){
      p[i-1] += x;
      p[i] -= x;
    }
  }
  int max2 = p[1];
  for (int i =2; i< n;i++){
    if (p[i]>max2){
      max2 = p[i];
    }
  }
  if (max2<max){
    goto sussy;
  }
  return max2;
}
