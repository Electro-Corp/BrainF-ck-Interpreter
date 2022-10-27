/*
  [BrainF*ck compiler]
  Unoptimized, but its small.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int memory[60000];
int current = 0;
char *code;
int i = 0;
void usage();
void parseCode(char code, int *memPx);
int main(int argv, char **args) {
  printf("The Lightweight Brainf*ck Interpter\n");
  // get file
  FILE *fp = fopen(args[1], "r");
  int c;
  size_t n = 0;
  if (fp == NULL) {
    usage();
    exit(1);
  }
  // read file
  code = malloc(1000);
  while ((c = fgetc(fp)) != EOF) {
    code[n++] = (char)c;
  }
  for (int g = 0; i < strlen(code); i++) {
    if (code[i]) {
      // printf("I IS: %d\n",i);
      parseCode(code[i], memory);
    }
  }
  printf("\n");
  return 0;
}
void usage() {
  printf("==== LWBFI ====\n");
  printf("Usage: \n");
  printf("./lwbfi filename\n");
}
int occ(char oc, char *sus) {
  int u = 0;
  for (int j = 0; j < strlen(sus); j++) {
    if (sus[j] == oc) {
      u++;
    }
  }
  return u;
}
void parseCode(char ch, int *memPx) {
  // if(ch)
  // printf("%c\n",ch);
  if (ch == '+') {
    memPx[current]++;
  }
  if (ch == '-') {
    memPx[current]--;
  }
  if (ch == '>') {
    current++;
  }
  if (ch == '<') {
    current--;
  }
  if (ch == '[') {
    char *sus = malloc(strlen(code));
    int h = 0;
    while (1) {
      if (i < strlen(code)) {
        if (code[i++]) {
          printf("CODE: %c\n",code[i]);
          if (code[i] != ']') {
            if ((occ('[', sus) == 0 && occ(']', sus) == 0) ||
                (occ('[', sus) != occ(']', sus))) {
              sus[h++] = code[i];
            }
          } else {
            if ((occ('[', sus) != 0 && occ(']', sus) != 0) &&
                (occ('[', sus) == occ(']', sus)))
              break;
            else {
              sus[h++] = code[i];
            }
          }
        }
      } else {
        break;
      }
    }
    h = 0;
    printf("SUS = %s \n", sus);
    while (memPx[current] > 0) {
      if (sus[h]) {
        if (h + 1 <= strlen(sus)) {
          parseCode(sus[h++], memPx);
        } else
          h = 0;
      }
    }
    // i += strlen(sus);
  }
  if (ch == '.') {
    putchar(memPx[current]);
  }
  if (ch == ',') {
    memPx[current] = (int)getchar();
  }
}