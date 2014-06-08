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
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <pthread.h>
#include "include/server.h"
#include "include/client_care.h"
#include "../flags/flags.h"

/* Global Variableused for signal handler ( I know not a good idea ) */
Server* server;
int fifo_fd;

/* HANDLER FUNCTION FOR SIGNAL */
void handle_function(){
    if(DEB_SERVER)printf("\n=== Signal get! Server is cleaning his mess and stop ===\n");
    close(fifo_fd); /*close the fifo*/
    unlink(server->fifo_path); /*unlink the fifo*/
    /*if unlink operation dosn't remove fifo, remove it*/
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
    parsed_msg* p;

    int i=0;
    pthread_t v_t[30];

    if(DEB_SERVER) printf("[!!!] SERVER IS RUNNING IN DEBUG MODE [!!!]\n");
    init_handler();

    server = alloc_server();
    server->args = parse_args(argc, argv);
    if( (server->fifo_path = set_fifo_path(server->args->name)) == NULL){
        printf("error: other server already found with name %s\n", server->args->name);
        exit(1);
    }
    server->encoded_file_path = set_encoded_file(server->args->name);

    if(DEB_SERVER) printf("[INFO] server set properly\n");

    /* create well known fifo if does’t exist */
    if( mkfifo(server->fifo_path, (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) ) { 
        if( errno != EEXIST ) {
            perror( " Cannot create well known fifo " );
            exit(1);
        }
    }
    printf(">>>> Server is running with name: %s\n", server->args->name );
    
    /*rw because doesn't work without it*/
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
        if(DEB_SERVER){
            printf("=== client message recived ===\n");
            printf("nbytes: %d\n", nbytes);
            printf("message: %s\n", buff);
        }
        
        p = read_client_buffer(server->args->name, buff);
        if(DEB_SERVER){
            printf("=== parsed message structure ===\n");
            print_parsed_msg(p);
        }
        
        /*check params of server*/
        if( p->in_msg != NULL ){
            if( strlen(p->in_msg) > server->args->msgmax )
                p->error = "ERROR: Server rejected message. Reason too long.";
        }
        if( p->key != NULL ){
            if( strlen(p->key) < server->args->keymin )
                p->error = "ERROR: Server rejected key. Reason too short.";
            else if( strlen(p->key) > server->args->keymax )
                p->error = "ERROR: Server rejected key. Reason too long.";
        }
        
        pthread_create(&v_t[i++], NULL, &pthread_handler, (void*)p );
        if(i>=30)i=0;

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
   
    if(DEB_SERVER) print(s);
    return s;
}
