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
  printf("The Lightweight Brainf*ck Interpeter\n");
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
  printf("===============\n");
  printf("File not found, or file not provided.\n");
}
int occ(char oc, char *loopVar) {
  int u = 0;
  for (int j = 0; j < strlen(loopVar); j++) {
    if (loopVar[j] == oc) {
      u++;
    }
  }
  return u;
}
void parseCode(char ch, int *memPx) {
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
    char *loopVar = malloc(strlen(code));
    int h = 0;
    while (1) {
      if (i < strlen(code)) {
        if (code[i++]) {
          if (code[i] != ']') {
            if ((occ('[', loopVar) == 0 && occ(']', loopVar) == 0) ||
                (occ('[', loopVar) != occ(']', loopVar))) {
              loopVar[h++] = code[i];
            }
          } else {
            if (((occ('[', loopVar) != 0 && occ(']', loopVar) != 0) &&
                (occ('[', loopVar) == occ(']', loopVar))) || occ('[',loopVar) == 0)
              break;
            else {
              loopVar[h++] = code[i];
            }
          }
        }
      } else {
        break;
      }
    }
    h = 0;
    while (memPx[current] > 0) {
        if (h + 1 <= strlen(loopVar)) {
          parseCode(loopVar[h++], memPx);
        } else
          h = 0;
      
    }
  }
  if (ch == '.') {
    putchar(memPx[current]);
  }
  if (ch == ',') {
    memPx[current] = (int)getchar();
  }
}