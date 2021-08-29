#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){

  int N, i, j, diag_1 = 0, diag_2 = 0;
  int matrix[150][150];
  int sumrow[150], sumcol[150];
  bool isMagic = true;
  bool found[150*150];

  for(i=0;i<150;i++)
    sumrow[i] = sumcol[i] = 0;
  for(i=0;i<150*150;i++)
    found[i] = false;

  scanf("%d",&N);
  while(N<1 || N>150)
    scanf("%d",&N);

  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      scanf("%d",&matrix[i][j]);
    }
  }

  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      if(found[matrix[i][j]] == true){
        isMagic = false;
      }else{
        found[matrix[i][j]]= true;
      }
    }
  }

  for(i=0;i<=N*N-1;i++){
    if(found[i] == false){
      isMagic = false;
      break;
    }
  }

  if(!isMagic){
    printf("no\n");
    return 0;
  }

  for(i=0;i<N;i++){
    diag_1 += matrix[i][i];
    for(j=0;j<N;j++){
      if(i+j == N-1){
        diag_2 += matrix[i][j];
      }
      sumrow[i] += matrix[i][j];
      sumcol[j] += matrix[i][j];
    }
  }

  if(diag_1 != diag_2 || diag_1 != sumrow[0]){
    isMagic = false;
    printf("no\n");
    return 0;
  }
  for(i=0;i<N;i++){
    if(sumrow[0] != sumrow[i] || sumrow[0] != sumcol[i]){
      isMagic = false;
      printf("no\n");
      return 0;
    }
  }

  if(isMagic){
    printf("yes\n");
    return 0;
  }

  return 0;

}  
