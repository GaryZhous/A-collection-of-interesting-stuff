#include <stdio.h>
#include <string.h>

int main(void){
    char grid[5][10] = {0};
    char (*p)[10] = grid;
    for(int i = 0; i<sizeof(grid)/sizeof(p[1]);i++)
      for(int j = 0; j < sizeof(p[1])/sizeof(p[1][1]) - 1;j+=2){
        p[i][j] = '*';
        if(j < 8)
          p[i][j+1] = ' ';
        }
    for(int i = 0;i<sizeof(grid)/sizeof(p[1]);i++)
      printf("%s\n", p[i]);
    return 0;
}
