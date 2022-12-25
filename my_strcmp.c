#include <stdio.h>

int my_strcmp(const char* str1, const char* str2){
    unsigned char s1, s2;
    while(1){
        s1 = *str1++;
        s2 = *str2++;
        if(s1 != s2)
            return s1 < s2 ? -1 : 1;
        if(!s1)
            break;
    }
    return 0;
}

int main(void){
    int ret = 0;
    ret = my_strcmp("abc", "abc");
    printf("abc:abc=%d\n", ret);
    ret = my_strcmp("abc", "abcdef");
    printf("abc:abcdef=%d\n", ret);
    return 0;
}
