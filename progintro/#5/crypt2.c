#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isValid(char key[26]){

  int i;
  bool found[26];

  for(i=0;i<26;i++)
    found[i] = false;

  for(i=0;i<26;i++){
    if(found[(int) key[i] - 'a'] == false){
      found[(int) key[i] - 'a'] = true;
    }else{
      return false;
    }
  }

  for(i=0;i<26;i++){
    if(found[i] == false){
      return false;
    }
  }

  return true;

}

int encrypt(int c, char key[26]){

  if(c >= 'a' && c <= 'z'){
    return key[c - 'a'];
  }else{
    if(c >= 'A' && c <= 'Z'){
      return key[c - 'A'] - ('a' - 'A');
    }else{
      return c;
    }
  }

}

int decrypt(int c, char key[26]){

  int i;
  char norm[26];

  for(i=0;i<26;i++){
    norm[i] = i + 'a';
  }

  i = 0;

  if(c >= 'a' && c <= 'z'){
    while(c != key[i]){
      i++;
    }
    return norm[i];
  }else{
    if(c >= 'A' && c <= 'Z'){
      c += ('a' - 'A');
      while(c != key[i]){
        i++;
      }
      return norm[i] - ('a' - 'A');
    }else{
      return c;
    }
  }

}

int main(){

  int i, c, select;
  char key[26];

  for(i=0;i<26;i++)
    key[i] = getchar();

  while(getchar() != '\n');

  if(!isValid(key)){
    printf("error\n");
    return 0;
  }

  select = getchar();
  while(getchar() != '\n');

  switch(select){

    case 'd':
      while((c = getchar()) != EOF){
        printf("%c",decrypt(c, key));
      }
      break;
    case 'e':
      while((c = getchar()) != EOF){
        printf("%c",encrypt(c, key));
      }
      break;
    default:
      printf("error\n");
      break;

  }

  return 0;

}  
