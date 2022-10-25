#include <stdio.h>
#include <stdlib.h>
int memory[60000];
int current = 0;
int inLoop = 0;
char *code;
int i = 0;
void usage();
void parseCode(char code);
int main(int argv, char **args) {
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
  // printf("Got: %s\n", code);
  for (int g = 0; i < 1000; i++) {
    if (code[i])
      parseCode(code[i]);
  }
  free(code);
  return 0;
}
void usage() {
  printf("==== LWBFI ====\n");
  printf("Usage: \n");
  printf("./lwbfi filename\n");
}
void parseCode(char ch) {
  if (ch == '+') {
    memory[current]++;
  }
  if (ch == '-') {
    memory[current]--;
  }
  if (ch == '>') {
    current++;
  }
  if (ch == '<') {
    current--;
  }
  if (ch == '[') {
    inLoop = 1;
    char *sus = malloc(1000);
    int h = i + 1;
    while (code[h++] != ']') {
      if (code[h])
        sus[h - i] = code[h];
    }
    while (memory[current] < 0) {
      if (h < strlen(sus))
        parseCode((char)sus[h++]);
      else
        h = 0;
    }
    i += strlen(sus);
  }
  if (ch == '.') {
    putchar(memory[current]);
  }
  if (ch == ',') {
    memory[current] = (int)getchar();
  }
}