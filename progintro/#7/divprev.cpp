#include <iostream>
#include <cstdlib>

int main(){
  int N, i, j, min = 0;
  int *A;

  scanf("%d", &N);
  A = (int *)malloc(sizeof(int) * N);

  for(i=0;i<N;i++){
    scanf("%d", &A[i]);
  }

  for(i=1;i<N;i++){
    j = i - 1;
    while(j >= 0){
      if(A[j] % A[i] == 0){
        j--;
      }else{
        break;
      }
    }
    if(j < 0){
      if(min == 0){
        min = A[i];
      }
      if(A[i] < min){
        min = A[i];
      }
    }
  }

  if(min != 0){
    printf("%d\n", min);
  }else{
    printf("%d\n", A[0]);
  }

  free(A);

  return 0;
}
