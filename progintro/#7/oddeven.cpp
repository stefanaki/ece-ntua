#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main() {
  int *A;
  int N, i, j, best = 0, wide;
  int mod2Counter, notMod2Counter;
  cin >> N;
  A = (int *)malloc(sizeof(int) * N);
  for(i=0;i<N;i++){
    cin >> A[i];
  }

 for(i=0;i<N;i++){
   wide = mod2Counter = notMod2Counter = 0;
   for(j=i;j<N;j++){
     if(A[j] % 2 == 0){
       mod2Counter++;
     }else{
       notMod2Counter++;
     }
     if(mod2Counter == notMod2Counter){
       wide = j-i+1;
     }
   }

  if(best < wide){
    best = wide;
  }
 }

  cout << best << endl;

  free(A);

  return 0;
}  
