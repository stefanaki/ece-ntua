#include <stdio.h>
#include <stdlib.h>

int main(){

    int N, M, min, max, i, j;
    int array[100][100];
    int line[100], col[100];

    scanf("%d %d",&N,&M);
    while(N<1 || N>100 || M<1 || M>100)
        scanf("%d %d",&N,&M);

    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            scanf("%d",&array[i][j]);
        }
    }

    for(j=0;j<M;j++){
        col[j] = array[0][j];
        for(i=0;i<N;i++){
            if(array[i][j] > col[j])
                col[j] = array[i][j];
        }
    }

    for(i=0;i<N;i++){
        line[i] = array[i][0];
        for(j=0;j<M;j++){
            if(array[i][j] < line[i])
                line[i] = array[i][j];
        }
    }

    max = line[0];
    min = col[0];

    for(i=0;i<N;i++)
        if(line[i] > max)
            max = line[i];
    for(j=0;j<M;j++)
        if(col[j] < min)
            min = col[j];

    printf("%d\n%d\n",min,max);


    return 0;

}  
