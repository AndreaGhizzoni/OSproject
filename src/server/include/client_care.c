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
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "client_care.h"
#include "server.h"
#include "../../util/cipher.h"

#define P_DEBUG 1

void manage_encode( int fifo_fd, parsed_msg* p){
    if( p->i_mode == 'm' ){
        if( p->o_mode == 'o' ){
            write_on_file( p->out_file, encode( p->key, p->in_msg ) );
        }else if( p->o_mode == 'c'){
            write_on_fifo(fifo_fd, encode(p->key,p->in_msg) ); 
        }
    }else if( p->i_mode == 'i'){
        if( p->o_mode == 'c' ){
            read_f( p->in_file, 100, fifo_fd, NULL, 'e', p->key );
        }else if( p->o_mode == 'o' ){
            read_f( p->in_file, 100, fifo_fd, p->out_file, 'e', p->key );
        }
    }
}

void manage_decode( int fifo_fd, parsed_msg* p){

}

void manage_list( int fifo_fd, parsed_msg* p){

}

void* pthread_handler(void* p_m){
    int fifo_client_fd;
    parsed_msg* p_msg = p_m;
    /*TODO check if null*/char* fifo_client = fifo_client_path(p_msg->pid);
    if(P_DEBUG) printf("> fifo path to the client created as %s\n", fifo_client );

    if( mkfifo( fifo_client, (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) ) ){
        if( errno != EEXIST ){
            perror(" Can not create fifo pthread -> client  ");
            exit(1);
        }
    }
    if(P_DEBUG) printf("> fifo to the client created..\n");

    fifo_client_fd = open_fifo_client(fifo_client);
    if(P_DEBUG) printf("> fifo to the client opened..");

    /*write response to client*/
    if( p_msg->error != NULL ){
        write_on_fifo( fifo_client_fd, p_msg->error );
    }else{
        switch(p_msg->what_to_do){
            case 'e': manage_encode(fifo_client_fd, p_msg); break;
            case 'd': manage_decode(fifo_client_fd, p_msg); break;
            case 'l': manage_list(fifo_client_fd, p_msg); break;
            default: write_on_fifo( fifo_client_fd, "ERROR\0");
        }
        write_on_fifo( fifo_client_fd, NULL );
    }

    /*TODO unlink and remove response fifo*/
    return NULL;
}

void write_on_fifo( int fifo_fd, char* msg ){
    int nbytes; char* buff=(char*)malloc(4096*sizeof(char));
    int msg_len;
    if( msg == NULL ) msg_len = -1;
    else msg_len = sizeof(char)*strlen(msg);
    
    sprintf(buff, "%d", msg_len);
    nbytes = write(fifo_fd, buff, 4);
    if( nbytes == -1 ){
        printf("Error to send %s", buff);
        exit(1);
    }

    if( msg_len != -1 ){
        sprintf(buff, "%s", msg);
        nbytes = write(fifo_fd, buff, msg_len);
        if( nbytes == -1 ){
            printf("Error to send %s", buff);
            exit(1);
        }
    }

    free(buff);
}

void write_on_file(char* output_file, char* msg){
    FILE* stream = fopen(output_file, "a");
    fputs(msg, stream);
    fputs("\n", stream);
    fflush(stream);
    fclose(stream);
}

void read_f(char* inf, int max_len, int fifo_fd, char* of, char mode, char* key ){
    FILE* stream = fopen(inf, "r");
    ssize_t read; 
    size_t len = max_len;
    char* line = NULL;

    if(stream == NULL)
        printf("fopen ret null on %s\n", inf);
    else
        printf("not null");

    while( (read = getline(&line, &len, stream) ) != -1 ){
        if( mode == 'e' ){
            if( of == NULL ){
                write_on_fifo( fifo_fd, encode(key, line) );
            }else
                write_on_file( of, encode(key,line) );
        }else if( mode == 'd' ){
            if( of == NULL )
                write_on_fifo( fifo_fd, decode(key, line) );
            else
                write_on_file( of, decode(key,line) );
        }else if( mode == 'l' ){

        }
    }

    fclose(stream);
}

char* fifo_client_path(char* pid){
    int c = strlen(pid)+strlen("/tmp/.fifo")+1;
    char* f = malloc( sizeof(char)*c);
    sprintf(f, "/tmp/%s.fifo", pid);

    if( access(f, F_OK ) != -1 )
        return NULL;
    
    return f;
}

int open_fifo_client(char* fifo_path){
    int fifo = open(fifo_path , O_RDWR );
    if( fifo < 0 ){
        perror("Can not open response fifo: pthread -> client");
        exit(-1);
    }
    return fifo;
}
