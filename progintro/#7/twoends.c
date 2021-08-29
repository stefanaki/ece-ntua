#include <stdio.h>
#include <stdlib.h>

int a[10000000];

int main(){
  int N, i;
  int left, right;
  int leftsum = 0, rightsum = 0;
  int s = 0;

  scanf("%d",&N);

  for(i=1;i<=N;i++){
    scanf("%d",&a[i]);
  }

  left = 0;
  right = N+1;

  while(left < right){
    if(leftsum == rightsum){
      s = rightsum;
      left++;
      right--;
      rightsum += a[right];
      leftsum += a[left];
    }else if(leftsum > rightsum){
        right--;
        rightsum += a[right];
    }else{
      left++;
      leftsum += a[left];
    }
  }

  printf("%d\n",s);

  return 0;
} 
