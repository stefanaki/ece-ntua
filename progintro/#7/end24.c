#include <stdio.h>

int main(){

    int N;
    scanf("%d",&N);

    if ((N*N) % 100 == 24)  printf("yes\n");
    else    printf("no\n");

    return 0;
}  
