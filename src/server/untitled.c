#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* read_mode(char* msg, int start, int end) {
  char* mode= (char*)malloc( sizeof(char)*(end-start));
  strncpy(mode, (msg+start), (end-start));
  mode[end-start]='\0';
  return mode;
}

char* read_buffer(char* msg, int len) {
  char *pid, *mode, *input, *output;
  int m=0, start=0, end=0;

  while (m!=4) {
    start=end;
    while(msg[end]!='|' && msg[end]!='\0') {
      end++;
    }

    switch (m) {
      case 0: {
        pid= read_mode(msg, start, end);
        break;
      }
      case 1: {
        mode= read_mode(msg, start, end);
        break;
      }
      case 2: {
        input= read_mode(msg, start, end);
        break;
      }
      case 3: {
        output= read_mode(msg, start, end);
      }
    }
    m++;
    end++;
  }
  printf("%s\n",pid );
  printf("%s\n",mode );
  printf("%s\n",input );
  printf("%s\n",output );
}

int main() {
  char* s= "6657|d;rfgdutrs|i;../lol/qwertyu|;\0";
  read_buffer(s, strlen(s));
  return 0;
}
