/* ============================== AUTHORS =====================================
# Federica Lago 157955
# Andrea Ghizzoni 157507
# PROJECT: #1 CODEC
# COURSE: Sistemi Operativi
# YEAR: 2014
=============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "include/server.h"

#define DEBUG 1

/* Global Variableused for signal handler ( I know not a good idea ) */
Server* server;


/* HANDLER FUNCTION FOR SIGNAL */
void handle_function(){
    printf("\nSignal get\n");
    /*close the fifo*/
    /*unlink the fifo*/
    /*if unlink operation dosn't remove fifo file, remove it*/
    exit(0);
}
/* HANDLER FUNCTION FOR SIGNAL */

Server_args* parse_args(int, char**);
void init_handler();

int main(int argc, char** argv){
    if(DEBUG) printf("[!!!] SERVER IS RUNNING IN DEBUG MODE [!!!]\n");

    init_handler();

    server = alloc_server();
    server->args = parse_args(argc, argv);
    server->encoded_file_path = set_encoded_file(server->args->name);
    if( (server->fifo_path = set_fifo_path(server->args->name)) == NULL){
        printf("error: other server already found with name %s\n", server->args->name);
        exit(1);
    }

    if(DEBUG) printf("[INFO] server set properly\n");

    /* create well known fifo if does’t exist */
    if( mkfifo(server->fifo_path, (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) ) { 
        if( errno != EEXIST ) {
            perror( " Cannot create well known fifo " );
            exit(1);
        }
    }
    printf(">>>> Server is running with name: %s\n", server->args->name );

    /* Main body loop */
    while(1){


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
