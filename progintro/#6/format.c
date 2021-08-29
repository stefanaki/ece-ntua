#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define LineLength 60
#define WordLength 20

void alignment(char line[], int ll, int lp){
  int fs = ll - lp + 1;
  int q = lp - 2;
  int k = q;
  int i;

  while(fs > 0){
    while(k > 0 && line[k] != ' '){
      k--;
    }
    if(k > 0){
      for(i=q;i>k;i--){
        line[i+1] = line[i];
      }
      line[k+1] = ' ';
      while(line[k] == ' '){
        k--;
      }
      q++;
      fs--;
    }else{
      k = q;
    }
  }

  line[ll] = '\n';

  return;
}

int updateLine(char line[], int lp , char word[], int wp){
  int i;

  for(i=0;i<=wp;i++){
    line[lp] = word[i];
    lp++;
  }

  return lp;
}

int main(){
  int wp, lp, i, c;
  char word[WordLength+2], line[LineLength+2];
  // FILE *infp, *outfp;

  // infp = fopen("in.txt","r");
  // outfp = fopen("out.txt","w");

  for(i=0;i<WordLength+2;i++){
    word[i] = '\0';
  }
  wp = 0;

  for(i=0;i<LineLength+2;i++){
    line[i] = '\0';
  }
  lp = 0;

  while((c = getc(stdin)) != EOF){
    if(!isspace(c)){
      word[wp] = c;
      wp++;
    }else{
      if(wp > 0){
        word[wp] = ' ';
        if(wp <= LineLength - lp){
          lp = updateLine(line, lp, word, wp);
        }else{
          alignment(line, LineLength, lp);
          // fprintf(outfp,"%s",line);
          printf("%s",line);
          for(i=0;i<LineLength+2;i++)
            line[i] = '\0';
          lp = 0;
          lp = updateLine(line, lp, word, wp);
        }
        wp = 0;
      }
    }
  }

  if(wp > 0){
    if(wp <= LineLength - lp){
      lp = updateLine(line, lp, word, wp);
      // fprintf(outfp,"%s",line);
      printf("%s",line);
    }else{
      alignment(line, LineLength, lp);
      // fprintf(outfp,"%s",line);
      printf("%s",line);
      wp = 0;
      for(i=0;i<LineLength+2;i++)
        line[i] = '\0';
      lp = 0;
      lp = updateLine(line, lp, word, wp);
      // fprintf(outfp,"%s",line);
      printf("%s",line);
    }
  }else{
    alignment(line, lp-1, lp);
    // fprintf(outfp,"%s",line);
    printf("%s",line);
  }

  return 0;
}  
