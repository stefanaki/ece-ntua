#include <stdio.h>

int main(){

    int N;

    scanf("%d",&N);
    if (N / 100 != 0 && N / 1000 == 0)  printf("yes\n");
    else    printf("no\n");

    return 0;
}  
