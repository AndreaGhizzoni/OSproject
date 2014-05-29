/* ============================== AUTHORS =====================================
# Federica Lago 157955
# Andrea Ghizzoni 157507
# PROJECT: #1 CODEC
# COURSE: Sistemi Operativi
# YEAR: 2014
=============================================================================*/

#include "server.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

Server* alloc_server(){
    Server* s = malloc( sizeof(Server) );
    s->args = NULL;
    s->fifo_path = NULL;
    return s;
}

char* set_fifo_path(char* s){
    char* fifo;
    int c;
    if(s== NULL)
        return NULL;
    
    c = strlen(s)+strlen("/tmp/.fifo");
    fifo = malloc(sizeof(char)*c);
    sprintf(fifo, "/tmp/%s.fifo", s);

    return fifo;    
}

char* substr(char* msg, int start, int end){
    char* mode = (char*) malloc( sizeof(char)*(end-start) );
    strncpy(mode, (msg+start), (end-start));
    mode[end-start]='\0';
    return mode;
}

void read_client_buffer(char* msg, int len) {
    char *pid; char* mode; char* input; char* output;
    int m=0; int start=0; int end=0;

    while (m!=4) {
        start=end;
        while(msg[end]!='|' && msg[end]!='\0') {
            end++;
        }

        switch(m){
            case 0:{
                pid = substr(msg, start, end);
                break;
            }
            case 1:{
                mode = substr(msg, start, end);
                break;
            }
            case 2:{
                input = substr(msg, start, end);
                break;
            }
            case 3:{
                output = substr(msg, start, end);
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
