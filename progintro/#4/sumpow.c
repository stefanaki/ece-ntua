#include <stdio.h>
#include <math.h>

int main(){

  int N, i, j, x, copy;
  long int powered_digits[10] = {0,0,0,0,0,0,0,0,0,0}, sum;

  scanf("%d",&N);

  for(i=0;i<10;i++)   powered_digits[i] = pow(i,N);

  for(i=0;i<=99999999;i++){
    sum = 0;
    copy = i;
    for(j=0;j<8;j++){
      x = copy % 10;
      copy /= 10;
      sum += powered_digits[x];
    }

    if(sum == i){
      printf("%d\n",i);
    }
  }


  return 0;

}  
