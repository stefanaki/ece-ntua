#include "pzhelp"
#include <cstdio>

int main(){

    int N, a;
    int i;

    scanf("%d",&N);

    if (N >= 10){

        for (i=1;i<=2;i++){

            a = N % 10;
            N /= 10;

        }

        printf("%d\n",a);

    }

    return 0;

}  
