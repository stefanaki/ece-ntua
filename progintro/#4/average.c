#include <stdio.h>
#include <stdlib.h>

int main(){

  float array[100][100], avg_col[100];
  int N, M, i, j;
  float result = 0.0;

  for(i=0;i<100;i++)
    avg_col[i] = 0;

  scanf("%d %d",&N,&M);
  for(i=0;i<N;i++){
    for(j=0;j<M;j++){
      scanf("%f",&array[i][j]);
    }
  }

  for(j=0;j<M;j++){
    for(i=0;i<N;i++){
      avg_col[j] += array[i][j];
    }
    avg_col[j] /= N;
  }

  for(j=0;j<M;j++){
    result += avg_col[j];
  }
  result /= M;

  printf("%.3lf\n%.3lf\n",result,result);

  return 0;

}  
