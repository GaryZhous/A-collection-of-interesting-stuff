#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(){
  srand(time(NULL));
label2:
  int number = rand()%100;
  cout << "Enter your guess: ";
label1:
  int idx = 0;
  char* buff = (char*)malloc(idx);
  char c;
  while((c=getchar()) !='\n'){
    buff = (char*)realloc(buff, ++idx);
    *(buff+idx-1)=c;
  }
  buff = (char*)realloc(buff, ++idx);
  buff[idx-1] = '\0';
  int mod = atoi(buff);
  if(mod != number){
    for(int i = 0; i < idx-1; i++){
      if(buff[i] > '9' || buff[i] < '0'){
        cout << "Enter a number, sir! ";
        goto label1;
      }
    }
    free(buff);
    if(mod > number){
      cout << "guess a smaller one: ";
      goto label1;
    }else{
      cout << "guess a bigger one: ";
      goto label1;
    }
  }
  string n;
  cout << "your answer is right! enter 0 to quit, else go on: ";
  getline(cin, n);
  const char* h = n.c_str();
  if(h[0] != '0')
    goto label2;
  cout << "see ya!" << endl;
  return 0;
}
