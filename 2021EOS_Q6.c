#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern void convert(char*input, char*output, int length);
int main(void) {
char *input =
"I'd like to believe that this works just fine.\nBut then again it might not.\n";
char output[2048];
convert(input, output, 15);
printf("%s\n", output);
for(int i = 0; i <= strlen(output); i++) {
if (output[i] == ' ') {
output[i] = 'X';
}
}
printf("%s\n", output);
return 0;
  }
void convert(char *input, char *output, int length) {
  char *inputPtr = input;
  char *outputPtr = output;
  while (*inputPtr != '\0') {
    int counter = 0;
    int flag = 0;
    while (counter <= length && *inputPtr != '\0') {
      // Copy word from input to output
      while (*inputPtr != ' ' && *inputPtr != '\0') {
        *outputPtr++ = *inputPtr++;
      }
      // Increment counter by length of word and space character
      counter += (inputPtr - outputPtr) + 1;
      // Insert space character in output
      if (*inputPtr != '\0') {
        *outputPtr++ = *inputPtr++;
      }
      // Set flag if end of input string is reached
      if (*inputPtr == '\0') {
        flag = 1;
      }
    }
    // Insert newline character in output and go back to beginning of loop
    if (!flag) {
      *outputPtr++ = '\n';
    }
  }
  // Terminate output string
  *outputPtr = '\0';
}
