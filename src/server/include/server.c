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
#include <ctype.h>

Server* alloc_server(){
    Server* s = malloc( sizeof(Server) );
    s->args = NULL;
    s->fifo_path = NULL;
    return s;
}

parsed_msg* alloc_parsed_msg(){
    parsed_msg* p = malloc( sizeof(parsed_msg) );
    p->pid = NULL;
    p->what_to_do = 'x';
    p->i_mode='x';
    p->o_mode='x';
    p->key=NULL;
    p->in_file=NULL;
    p->in_msg=NULL;
    p->out_file=NULL;
    p->error=NULL;
    return p;    
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
    /*
    printf("%s\n",pid );
    printf("%s\n",mode );
    printf("%s\n",input );
    printf("%s\n",output );
    */
    parsed_msg* p = alloc_parsed_msg();

    parse_pid(p, pid);
    /*if(p->error != NULL) return p;*/

    parse_mode(p, mode);
    /*if(p->error != NULL) return p;*/

    parse_input(p, input);
    /*if(p->error != NULL) return p;*/

    parse_output(p, output);
    /*if(p->error != NULL) return p;*/

    /*return p;*/
}

void parse_pid(parsed_msg* p, char* pid){
    int i = 0;
    int r = 0;
    while( pid[i] != '\0' ){
        if( !isdigit(pid[i++]) ) r=-1;
    }

    if( r == -1 )
        p->error = "Client pid recived malformed by server.\0";
    else
        p->pid = pid;
}

void parse_mode(parsed_msg* p, char* mode){
    
}

void parse_input(parsed_msg* p, char* input){
    
}

void parse_output(parsed_msg* p, char* output){
    
}
