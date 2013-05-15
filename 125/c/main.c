#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isLetter(char c){
  if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <='z'))
    return 1;
  return 0;
}

int isDigit(char c){
  if(c >= '0' && c <= '9')
    return 1;
  return 0;
}

int isHiddenChar(char c){
  if(c == '\n' || c == '\t')
    return 1;
  return 0;
}

char lower(char c){
  if(c >= 'a' && c <= 'z')
    return c;
  return c + ('a' - 'A');
}

int letterStored(char *larr, char c){
  int i = 0;
  for(;i<26*2;i++){
    if(larr[i] == c)
      return i;
  }
  return -1;
}

void sort(char larr[], int occt[]){
  int i = 0;
  int j = 0;
  int max;
  for(i = 0; i< 26*2;i++){
    for(j = 0;j<26*2;j++){
      if(occt[i]>occt[j])
      {
        int aux = occt[i];
        occt[i] = occt[j];
        occt[j] = aux;
        char c_aux = larr[i];
        larr[i] = larr[j];
        larr[j] = c_aux;
      }
    }
  }
}

int main(int argc, char **argv){
  if(argc<2){
    printf("You have to specify the input as an argument\n");
    return -1;
  }

  unsigned nWords = 0;
  unsigned nLetters = 0;
  unsigned nSymbols = 0;
  unsigned char lettersArray[26*2] = {0};
  unsigned int  lettersOccArray[26*2] = {0};

  char *fname = argv[1];
  FILE *fp = fopen(fname, "r");
  if(!fp){
    printf("Error While opening the input file\n");
    return -1;
  }

  char c;
  short gotAspace = 0;
  short holdAword = 0;
  c = fgetc(fp);

  while(!feof(fp)){
    if(c != ' '){
      holdAword = 1;
    }
    if(c == ' ' && !gotAspace)
      gotAspace = 1;
    else
      gotAspace = 0;

    if(gotAspace && holdAword){
      holdAword = 0;
      gotAspace = 0;
      nWords++;
    }
    if(!isDigit(c) && !isLetter(c) && !isHiddenChar(c) && c != ' '){
      nSymbols++;
    }

    if(isLetter(c)){
      nLetters++;
      c = lower(c);
      int pos = letterStored(lettersArray, c);
      if(pos != -1)
        lettersOccArray[pos]++;
      else{
        lettersArray[strlen(lettersArray)] = c;
        lettersOccArray[letterStored(lettersArray,c)]++;
      }
    }

    c = fgetc(fp);
  }
  if(holdAword)
    nWords++;

  fclose(fp);

  printf("%u words\n",nWords);
  printf("%u letters\n",nLetters);
  printf("%u symbols\n",nSymbols);
  sort(lettersArray, lettersOccArray);
  printf("Top three most common letters : \"%c\", \"%c\", \"%c\"\n",lettersArray[0], lettersArray[1], lettersArray[2]);

  return 0;
}
