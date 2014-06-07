/* ============================== AUTHORS =====================================
# Andrea Ghizzoni 157507
# Federica Lago 157955
# PROJECT: #1 CODEC
# COURSE: Sistemi Operativi
# YEAR: 2014
=============================================================================*/

#include "client_args.h"
#include "interaction.h"
#include <limits.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define I_DEBUG 1

char* fifo_server_path(char* name){
    char* path = malloc( sizeof(char)*(strlen("/tmp/.fifo")+strlen(name)+1));
    sprintf(path, "/tmp/%s.fifo", name);
    return path;
}

int open_fifo_server(char* nameFifoServer){
    int fifo_server = open(nameFifoServer, O_WRONLY);
    if (fifo_server < 0) { 
        perror("Cannot open well known fifo"); 
        exit(-1); 
    }
    return fifo_server;
}

char* fifo_client_path(int pId){
    char* fifo_path;
    char* pid = (char*)malloc(sizeof(char)*6);
    sprintf( pid, "%d", pId );

    fifo_path = (char*)malloc(sizeof(char)*(strlen(pid)+strlen("/tmp/.fifo")+1));
    sprintf( fifo_path, "/tmp/%s.fifo", pid );
    
    return fifo_path;
}

int open_fifo_client(char* fifoname){
    int fifo_client = open(fifoname, O_RDWR);
    if( fifo_client < 0 ){ 
        perror("Cannot open fifo client"); 
        exit(-1); 
    }
    return fifo_client;
}

char* format_buffer(Client_args* c){
    char *pid, *mode, *input, *output, *msg;
    int lenall;

    pid = malloc( sizeof(char)*6);
    sprintf(pid, "%d", getpid());

    if( c->op==-1 ){
        mode = malloc( sizeof(char)*strlen("l;")+1);
        sprintf(mode, "l;");
        lenall = strlen(pid)+ strlen(mode)+3;
        msg = malloc( sizeof(char)*lenall );
        sprintf(msg, "%s|%s||", pid, mode);
    }else{                
        mode = malloc( sizeof(char)*(strlen(c->key)+3));
        if(c->op==0)
            sprintf(mode, "e;%s", c->key);
        else
            sprintf(mode, "d;%s", c->key);

        if(c->isFile==0){
            input = malloc( sizeof(char)*(strlen(c->message)+3));
            sprintf(input, "m;%s", c->message);
        }else{
            input = malloc( sizeof(char)*(strlen(c->fileName)+3));
            sprintf(input, "i;%s", c->fileName);
        }

        if(c->output==NULL){
            output = malloc( sizeof(char)*2);
            sprintf(output, ";");
        }else{
            output = malloc( sizeof(char)*(strlen(c->output)+3));
            sprintf(output, "o;%s", c->output);
        }

        lenall = strlen(pid)+strlen(mode)+strlen(input)+strlen(output)+4;
        msg = malloc( sizeof(char)*lenall );
        sprintf(msg, "%s|%s|%s|%s", pid, mode, input, output);
    }
    return msg;
}

void send_request(Client_args* c, int fifo_server){
    char* message;
    char buffer[PIPE_BUF];
    int msg_size, nread;

    /*write request*/
    message = format_buffer(c);
    msg_size = sizeof(char)*strlen(message);

    sprintf(buffer, "%d", msg_size);
    nread = write(fifo_server, buffer, 4);
    if( nread == -1 ){
        printf("error first nread" );
        exit(1);
    }

    sprintf(buffer, "%s", message);
    nread = write(fifo_server, buffer, msg_size); 
    if( nread == -1 ){
        printf("error second nread" );
        exit(1);
    }
}

void read_response( int fifo_fd ){
    int nbytes; char* buff;

    while(1){
        buff=(char*)malloc(4069*sizeof(char));
        if(I_DEBUG) printf("========= Tring to read message length\n");
        nbytes = read( fifo_fd, buff, 4);
        if(I_DEBUG){
            printf("=== Response from pthread ===\n");
            printf("nbytes: %d\n", nbytes);
            printf("buff: %s\n", buff);
        }
        
        /* end of comunication */
        if(atoi(buff) == -1 ){
            break;
        }else{
            if(I_DEBUG) printf("=== Tring to read message\n");
            nbytes = read( fifo_fd, buff, atoi(buff) );
            
            printf("%s\n", buff);
        }
        free(buff);
    }
}

void do_all(Client_args* c){
    char* path_response_fifo; int fifo_response_not_found; int fifo_response;
    int fifo_server = open_fifo_server(fifo_server_path(c->nameServer));
    send_request(c, fifo_server);
    close(fifo_server);

    fifo_response_not_found = 1;
    path_response_fifo = fifo_client_path(getpid());
    if(I_DEBUG)printf("=== Pending for response fifo at %s\n", path_response_fifo);
    while(fifo_response_not_found){
        if( access(path_response_fifo, F_OK) != -1 ){
            if(I_DEBUG)printf("=== Response fifo find!\n");
            fifo_response_not_found=0;
        }
    }

    fifo_response = open_fifo_client(path_response_fifo);
    if( fifo_response < 0 ){
        perror(" Can not open fifo response client <- pthread ");
        exit(1);
    }
    if(I_DEBUG) printf("=== Response fifo opend!\n");
    
    read_response(fifo_response);
}   
