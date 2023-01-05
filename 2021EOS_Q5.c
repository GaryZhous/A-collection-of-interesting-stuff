#include <stdio.h>
unsigned int generateInt(int list[], int size) {
  unsigned int result = 0;
  for (int i = 0; i < size; i++) {
    // Set the i-th bit of result to 1
    result |= (1 << list[i]);
  }
  return result;
}

int main(void) {
int list[] = {0, 3, 4, 9};
unsigned int result = generateInt(list, 4);
printf("result = %x\n", result);
return 0;
}
