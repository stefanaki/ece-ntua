#include "pzhelp"
#include <cstdio>

int main(){

    int N;
    scanf("%d",&N);
    if (N%7 == 0 && N%6 != 0)   printf("yes\n");
    else    printf("no\n");

    return 0;
}  
