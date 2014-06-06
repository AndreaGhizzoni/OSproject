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
    s->encoded_file_path = NULL;
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

char* set_encoded_file(char* server_name){
    int len = strlen(server_name)+strlen("/tmp/.list")+1;
    char* output_file = (char*)malloc( sizeof(char)*len );
    sprintf(output_file, "/tmp/%s.list", server_name);

    if( access(output_file, F_OK ) == -1 )
        fclose(fopen(output_file, "w"));

    return output_file;
}

char* substr(char* msg, int start, int end){
    char* mode = (char*) malloc( sizeof(char)*(end-start) );
    strncpy(mode, (msg+start), (end-start));
    mode[end-start]='\0';
    return mode;
}

parsed_msg* read_client_buffer(char* server_name, char* msg, int len) {
    char *pid=""; char* mode=""; char* input=""; char* output="";
    int m=0; int start=0; int end=0;
    parsed_msg* p;

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
    p = alloc_parsed_msg();

    parse_pid(p, pid);
    if(p->error != NULL) return p;

    parse_mode(p, mode);
    if(p->error != NULL) return p;

    parse_input(p, input);
    if(p->error != NULL) return p;

    parse_output(p, output);
    if(p->error != NULL) return p;

    p->server_name = server_name;

    return p;
}

void parse_pid(parsed_msg* p, char* pid){
    int i = 0; int r = 0;
    while( pid[i] != '\0' ){
        if( !isdigit(pid[i++]) ){ r=-1; break; }
    }

    if( r == -1 )
        p->error = "ERROR: Client pid recived malformed by server.\0";
    else
        p->pid = pid;
}

void parse_mode(parsed_msg* p, char* mode){
    if( mode[1] != ';'){
        p->error = "ERROR: Malformed mode separator.\0";
    }else{
        if(mode[0] == 'e' || mode[0] == 'd'){
            p->what_to_do = mode[0];
            p->key = substr(mode, 2, strlen(mode));
        }else if(mode[0] == 'l'){
            p->what_to_do = mode[0];
        }else{
            p->error = "ERROR: Unricognized mode command from client message\0";
        }
    } 
}

void parse_input(parsed_msg* p, char* input){
    if( input[1] != ';'){
        p->error = "ERROR: Malformed input separator.\0";
    }else{
        if(input[0] == 'i' ){
            p->i_mode = input[0];
            p->in_file = substr(input, 2, strlen(input));
        }else if(input[0] == 'm'){
            p->i_mode = input[0];
            p->in_msg = substr(input, 2, strlen(input));
        }else{
            p->error = "ERROR: Unricognized input command from client message\0";
        }
    } 
}

void parse_output(parsed_msg* p, char* output){
    if(output[0] == ';'){
        p->o_mode = 'c';
    }else{
        if(output[1] == ';'){
            if(output[0] == 'o'){
                p->o_mode = output[0];
                p->out_file = substr(output, 2, strlen(output));
            }else{
                p->error = "ERROR: Unricognized output command from client message\0";
            }
        }else{
            p->error = "ERROR: Malformed output separator.\0";
        }
    }
}

void print_parsed_msg(parsed_msg* p){
    printf("pid: %s\n", p->pid);
    printf("what_to_do: %c\n", p->what_to_do);
    printf("i_mode: %c\n", p->i_mode);
    printf("key: %s\n", p->key);
    printf("in_file: %s\n", p->in_file);
    printf("in_msg : %s\n", p->in_msg);
    printf("o_mode: %c\n", p->o_mode);
    printf("out_file: %s\n", p->out_file);
    printf("error: %s\n", p->error);
}
