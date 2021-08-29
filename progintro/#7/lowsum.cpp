#include <iostream>
#include <cstdlib>
#include <math.h>

using namespace std;

int main(){
  int N, i, j, best;
  int sum;
  int *A;

  cin >> N;
  A = (int *)malloc(sizeof(int) * N);
  for(i=0;i<N;i++){
    cin >> A[i];
  }

  i = 0;
  j = N-1;

  best = A[i] + A[j];

  while(i < j){
    if(abs(best) > abs(A[i] + A[j])){
      best = A[i] + A[j];
    }
    if(A[i] + A[j] > 0){
      j--;
    }else if(A[i] + A[j] < 0){
      i++;
    }else{
      best = 0;
      break;
    }
  }

  cout << best << endl;

  free(A);

  return 0;
}  
