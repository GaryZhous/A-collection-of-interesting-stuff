#include <iostream>

int mhm(int a){
  if(a == 0)
    return 1;
  if(a == 1)
    return 1;
  return a*mhm(a-1);
}
int main(){
    int rows;
    std::cout << "Plz enter the number of lines: ";
    std::cin >> rows;
    int idx = rows-1;
    for(int i = 0;i<rows;i++){
      for(int j = 0;j<idx;j++)
        std::cout << " ";
      for(int g = 0;g<i+1;g++){
        std::cout << mhm(i)/(mhm(g)*mhm(i-g)) << " ";
      }
      std::cout << "\n";
      idx--;
    }
  return 0;
}
//my lazy design, the gap between each number is just hard to fix
