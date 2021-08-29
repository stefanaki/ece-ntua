#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
  int N, i, j, count = 0;
  int *Primes;

  scanf("%d",&N);
  while(N < 1 || N > 5000000){
    scanf("%d",&N);
  }

  Primes = (int *)malloc(sizeof(int) * (N+1));

  for(i=0;i<=N;i++){
    Primes[i] = 1;
  }

  Primes[0] = Primes[1] = 0;

  for(i=2;i<=sqrt(N);i++){
    if(Primes[i] == 1){
      for(j=i;i*j<=N;j++){
        Primes[i*j] = 0;
      }
    }
  }

  for(i=2;i<=N;i++){
    if(Primes[i] == 1){
      count++;
    }
  }

  printf("%d\n",count);

  free(Primes);

  return 0;
}  
