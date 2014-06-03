#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MSG_MAX 100      /*In server_args*/

char* create_output_file(char* server_name) {
  char* output_file = (char*)malloc( sizeof(char)*(strlen(server_name)+strlen("out_")+1));
  sprintf(output_file, "out_%s", server_name);
  fclose(fopen(output_file, "w"));

  output_file = realpath(output_file, NULL);

  return output_file;
}

void write_encoded(char* msg, char* output_file) {
   FILE *stream;
   stream = fopen(output_file, "a");
   fputs(msg, stream);
   fclose(stream);
}

void read_encoded(char* output_file, char* server_name) {
  FILE *stream;
  char* line;

  stream = fopen(output_file, "r");
  if (stream == NULL) {
    printf("No message has been encoded on %s\n", server_name);
    exit(1);
  }
  
  while(fgets(line, MSG_MAX, stream) != NULL) {
    printf("%s\n\n", line);                           /*TO DO not print but send it to client*/
  }
  fclose(stream);
}

int main () {
  char msg[]= "abcdefg";
  char server_name[]="server1";
  char output_file[]="out_server1";

  /*after decode*/
  if (output_file==NULL) {
    output_file = create_output_file(server_name);
  }
  write_encoded(msg, output_file);


  /*after list request*/
  read_encoded(output_file, server_name);

}