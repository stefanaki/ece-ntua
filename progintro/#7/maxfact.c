#include <stdio.h>

int main(){

    int N, temp;
    int i = 0;
    scanf("%d",&N);

    while(fact(i)<=N)    i++;

    i--;

    printf("%d\n",i);


    return 0;
}

int fact(int n){


    int f = 1;

    while(n>0){

        f *= n;
        n--;

    }

    return f;

}  
