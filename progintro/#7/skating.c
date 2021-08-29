#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
  int N, i, j, sum, best = 0;
  int *A;
  bool f;

  scanf("%d", &N);
  A = (int *)malloc(sizeof(int) * N);

  for(i=0;i<N;i++){
    scanf("%d", &A[i]);
    best += A[i];
  }

  sum = best;

  for(i=0;i<N;i++){
    sum -= A[i];
    if(sum > best){
      best = sum;
    }
  }

  if(best > 0){
    printf("%d\n", best);
  }else{
    printf("0\n");
  }

  free(A);

  return 0;
}
