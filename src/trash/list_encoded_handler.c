#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define MSG_MAX 100      /*In server_args*/
char* create_encoded_list_file(char* server_name){
    /*change .list with /tmp/.list*/
    int len = strlen(server_name)+strlen(".list")+1; /*why +1 ?*/
    char* output_file = (char*)malloc( sizeof(char)*len );
    sprintf(output_file, "%s.list", server_name);

    if( access(output_file, F_OK ) == -1 )
        fclose(fopen(output_file, "w"));

    return output_file;
}

void write_on_list(char* msg, char* output_file) {
    FILE* stream = fopen(output_file, "a");
    fputs(msg, stream);
    fputs("\n", stream);
    fflush(stream);
    fclose(stream);
}

void read_on_list(char* output_file, char* server_name) {
    FILE* stream = fopen(output_file, "r");
    ssize_t read; /*this will be the lien length*/
    size_t len = MSG_MAX;
    char* line = NULL;

    /*TODO not print but send it to client*/
    while( (read = getline(&line, &len, stream) ) != -1 ){
        printf("%s", line);
    }
    /*sand to the client a list terimaton*/

    fflush(stream);
    fclose(stream);
}

int main(int argc, char** argv) {
    //char* encoded_msg = "asdvhccwjncoweu\0";
    char* server_name = "server1\0";
    char* output_file = create_encoded_list_file(server_name);

    /*write_on_list("vrivv ugeveg\0", output_file);
    write_on_list("ajubwuicw dcw asdadecwhj0", output_file);
    write_on_list("jwbfi\0", output_file);
    write_on_list("asjcbiuwc biubeciu  qdiuweicu\0", output_file);
    write_on_list("achwdads asda u\0", output_file);
    */

    read_on_list(output_file, server_name);
}
