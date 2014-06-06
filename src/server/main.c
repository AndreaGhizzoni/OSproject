/* ============================== AUTHORS =====================================
# Federica Lago 157955
# Andrea Ghizzoni 157507
# PROJECT: #1 CODEC
# COURSE: Sistemi Operativi
# YEAR: 2014
=============================================================================*/
#define _GNU_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "include/server.h"

#define DEBUG 1

/* Global Variableused for signal handler ( I know not a good idea ) */
Server* server;
int fifo_fd;

/* HANDLER FUNCTION FOR SIGNAL */
void handle_function(){
    printf("\nSignal get\n");
    /*close the fifo*/
    close(fifo_fd);
    /*unlink the fifo*/
    unlink(server->fifo_path);
    /*if unlink operation dosn't remove fifo file, remove it*/
    remove(server->fifo_path);
    remove(server->encoded_file_path);
    exit(0);
}
/* HANDLER FUNCTION FOR SIGNAL */

Server_args* parse_args(int, char**);
void init_handler();

int main(int argc, char** argv){
    int nbytes; 
    char* buff; 
    if(DEBUG) printf("[!!!] SERVER IS RUNNING IN DEBUG MODE [!!!]\n");

    init_handler();

    server = alloc_server();
    server->args = parse_args(argc, argv);
    if( (server->fifo_path = set_fifo_path(server->args->name)) == NULL){
        printf("error: other server already found with name %s\n", server->args->name);
        exit(1);
    }
    server->encoded_file_path = set_encoded_file(server->args->name);

    if(DEBUG) printf("[INFO] server set properly\n");

    /* create well known fifo if does’t exist */
    if( mkfifo(server->fifo_path, (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) ) { 
        if( errno != EEXIST ) {
            perror( " Cannot create well known fifo " );
            exit(1);
        }
    }
    printf(">>>> Server is running with name: %s\n", server->args->name );
    
    fifo_fd = open( server->fifo_path, O_RDWR );
    if( fifo_fd < 0 ){
        perror( " Cannot open read only well known fifo " );
        exit(1);
    }
    
    
    /* Main body loop */
    while(1){
        buff = (char*)malloc(4069*sizeof(char));
        nbytes = read(fifo_fd, buff, 4); /*read the message length */
        nbytes = read(fifo_fd, buff, atoi(buff)); /*read the message */
        printf("%s\n", buff);
        printf("%d\n", nbytes);
        free(buff);
    }

    return 0;
}

void init_handler(){
    signal(SIGTERM, handle_function);
    signal(SIGKILL, handle_function);
    signal(SIGINT , handle_function);
}

Server_args* parse_args(int argc, char** argv){
    Server_args* s = populate(argc, argv);
    if(s == NULL)
        exit(1);
   
    if(DEBUG) print(s);
    return s;
}
