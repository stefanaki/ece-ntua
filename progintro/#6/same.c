#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int partition(int a[], int first, int last);

void swap(int *a, int *b){

  int temp;

  temp = *a;
  *a = *b;
  *b = temp;

}

void quickSort(int *a, int first, int last){

  int i;

  if(first >= last){
    return;
  }

  i = partition(a,first,last);
  quickSort(a,first,i);
  quickSort(a,i+1,last);

}

int partition(int a[], int first, int last){

  int x = a[(first + last)/2];
  int i = first, j = last;

  while(true){
    while(a[i] < x)
      i++;
    while(x < a[j])
      j--;
    if(i >= j)
      break;
    swap(&a[i],&a[j]);
    i++;
    j--;
  }

  return j;

}

int main(){

  int N, i, min, max;
  int A[50000], B[50000];
  bool maxFound = false, minFound = false;

  scanf("%d",&N);

  for(i=0;i<N;i++){
    scanf("%d",&A[i]);
  }
  for(i=0;i<N;i++){
    scanf("%d",&B[i]);
  }

  quickSort(A,0,N-1);
  quickSort(B,0,N-1);

  i = 0;

  while(A[i] == B[i] && i <= N-1){
    i++;
  }
  if(A[i] != B[i]){
    i--;
  }

  if(i < N-1){

    for(i=0;i<N;i++){

      if(A[N-i-1] != B[N-i-1] && !maxFound){
        if(A[N-i-1] > B[N-i-1]){
          max = A[N-i-1];
        }else{
          max = B[N-i-1];
        }
        maxFound = true;
      }

      if(A[i] != B[i] && !minFound){
        if(A[i] < B[i]){
          min = A[i];
        }else{
          min = B[i];
        }
        minFound = true;
      }

      if(maxFound && minFound){
        break;
      }

    }

    printf("no %d %d\n",min,max);

  }else{
    printf("yes\n");
  }

  return 0;

}  
