#include <iostream>

using namespace std;

int a[1000000];

int main(){
  int n, x;
  int i, j;
  int counter = 0;

  scanf("%d %d", &n, &x);
  for(i=0;i<n;i++){
    scanf("%d", &a[i]);
  }

  for(i=0;i<n-1;i++){
    if(a[i] >= x){
      continue;
    }
    for(j=i+1;j<n;j++){
      if(a[j] >= x){
        continue;
      }
      if(a[i] + a[j] == x){
        counter++;
      }
    }
  }

  printf("%d\n", counter);

  return 0;
}
