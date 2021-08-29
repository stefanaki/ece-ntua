#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

int main(){

  int N, i, j, k, numOfPalins = 0;
  float percentage;
  char symbolArray[21];
  bool isPalin, isLong = false;

  scanf("%d",&N);
  getchar();

  for(i=1;i<=N;i++){

    for(k=0;k<21;k++)
      symbolArray[k] = 0;

    isPalin = true;
    j = k = 0;
    if(isLong)
      while(getchar() != '\n');

    symbolArray[j] = getchar();
    if(symbolArray[j] == '\n'){
      printf("empty\n");
      isLong = false;
      continue;
    }

    while(symbolArray[j] != '\n' && j < 20){
      j++;
      symbolArray[j] = getchar();
    }

    if(j == 20 && symbolArray[20] != '\n'){
      printf("error\n");
      isLong = true;
      continue;
    }else{
      isLong = false;
      j--;
      while(j-k >= 1){
        if (symbolArray[k] != symbolArray[j]){
          isPalin = false;
          break;
        }else{
          k++;
          j--;
        }
      }

      if(isPalin){
        printf("yes\n");
        numOfPalins++;
      }else
        printf("no\n");
    }
  }

  percentage = ((float) numOfPalins / N) * 100;
  printf("%.3lf\n", percentage);

  return 0;

}  
