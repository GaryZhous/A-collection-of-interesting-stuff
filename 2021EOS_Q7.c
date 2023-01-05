#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern char *removeStringFromString(char *str, char * substr);
int main(){
  char *s = "Hello World!";
const char *p = removeStringFromString(s, "l");
const char *q = removeStringFromString(s, "el");
printf("%s\n", p);
printf("%s\n", q);
return 0;
}

char* removeStringFromString(char* str, char* substr) {
  //see if substr is longer than str
  switch (int a = strcmp(str, substr)){
    case (-1):{
      char* err = "substr is longer than str, failed!";
      return err;}
    default:{
      continue;
    }
  }
  // base case: if the substring is not present in the string, return the string as is
  if (!strstr(str, substr)) {
    return str;
  }
  
  // recursive case: create a new string with the first instance of the substring removed
  int index = strstr(str, substr) - str;
  int len = strlen(str);
  int sublen = strlen(substr);
  char* newstr = malloc(len - sublen + 1);
  strncpy(newstr, str, index);
  strncpy(newstr + index, str + index + sublen, len - index - sublen);
  newstr[len - sublen] = '\0';
  return removeStringFromString(newstr, substr);
}
