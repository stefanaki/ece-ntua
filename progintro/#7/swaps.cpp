#include <iostream>
#include <cstdlib>

using namespace std;

int main(){
  int N, i, j, first = 0, counter = 0, swaps = 0;
  int *A;

  scanf("%d", &N);
  A = (int *)malloc(sizeof(int) * N);

  for(i=0;i<N;i++){
    scanf("%d", &A[i]);
    if(A[i] > 0){
      counter++;
    }else if(A[i] < 0 && i > 0){
      first = A[i];
      for(j=i-1;j>=i-counter;j--){
        A[j+1] = A[j];
      }
      A[i - counter] = first;
      swaps += counter;
    }
  }

  printf("%d\n%d\n%d\n", swaps, A[0], A[N-1]);

  free(A);

  return 0;
}
