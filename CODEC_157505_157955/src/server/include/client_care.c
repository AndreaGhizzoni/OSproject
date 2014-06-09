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
#include "../../flags/flags.h"

void manage_encodedecode( int fifo_fd, parsed_msg* p, char mode ){
    char* tmp;
    if( p->i_mode == 'm' ){
        if( p->o_mode == 'o' ){
            if( mode == 'e' ){
                tmp = encode( p->key, p->in_msg );
                write_on_encoded_file( tmp, p->server_name );
            }else{
                tmp = decode( p->key, p->in_msg );
            }
              
            write_on_file( p->out_file, tmp );
        }else if( p->o_mode == 'c'){
            if(mode == 'e'){
                tmp = encode( p->key, p->in_msg );
                write_on_encoded_file( tmp, p->server_name );
            }
            else{ 
                tmp = decode(p->key,p->in_msg);
            }

            write_on_fifo(fifo_fd, tmp); 
        }
    }else if( p->i_mode == 'i'){
        if( p->o_mode == 'c' ){
            read_f( p->in_file, 100, fifo_fd, NULL, mode, p->key, p->server_name );
        }else if( p->o_mode == 'o' ){
            read_f( p->in_file, 100, fifo_fd, p->out_file, mode, p->key, p->server_name );
        }
    }
}

void manage_list( int fifo_fd, parsed_msg* p ){
    char* t = (char*)malloc(sizeof(char*)*(strlen(p->server_name)+strlen("/tmp/.list")));
    sprintf(t, "/tmp/%s.list", p->server_name);
    if( p->o_mode == 'c' )
        read_f(t, 100, fifo_fd, NULL, 'l', p->key, p->server_name );
    else if( p->o_mode == 'o' )
        read_f(t, 100, fifo_fd, p->out_file, 'l', p->key, p->server_name );
    free(t);
}

void* pthread_handler(void* p_m){
    int fifo_client_fd;
    parsed_msg* p_msg = p_m;
    char* fifo_client = fifo_client_path(p_msg->pid);
    if( fifo_client == NULL ) /*if is NULL there is another pthread thar is responding to client*/
        return NULL;

    if(DEB_SERVER) printf("[INFO] fifo path to the client created as %s\n", fifo_client );

    if( mkfifo( fifo_client, (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) ) ){
        if( errno != EEXIST ){
            perror(" Can not create fifo pthread -> client  ");
            exit(1);
        }
    }
    if(DEB_SERVER) printf("[INFO] fifo to the client created..\n");

    fifo_client_fd = open_fifo_client(fifo_client);
    if(DEB_SERVER) printf("[INFO] fifo to the client opened..\n");

    /*write response to client*/
    if( p_msg->error != NULL ){
        write_on_fifo( fifo_client_fd, p_msg->error );
    }else{
        switch(p_msg->what_to_do){
            case 'e': manage_encodedecode(fifo_client_fd, p_msg, 'e'); break;
            case 'd': manage_encodedecode(fifo_client_fd, p_msg, 'd'); break;
            case 'l': manage_list(fifo_client_fd, p_msg); break;
            default: write_on_fifo( fifo_client_fd, "ERROR\0");
        }
    }

    /*send termination message and unlink the fifo*/
    write_on_fifo( fifo_client_fd, NULL );
    unlink(fifo_client);
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
        printf("[ERR] Error to send %s", buff);
        exit(1);
    }

    if( msg_len != -1 ){
        sprintf(buff, "%s", msg);
        nbytes = write(fifo_fd, buff, msg_len);
        if( nbytes == -1 ){
            printf("[ERR] Error to send %s", buff);
            exit(1);
        }
    }

    free(buff);
}

void write_on_file(char* output_file, char* msg){
    FILE* stream = fopen(output_file, "ab+");
    fputs(msg, stream);
    fputs("\n", stream);
    fflush(stream);
    fclose(stream);
}

void write_on_encoded_file(char* msg, char* server){
    char* f = (char*)malloc(sizeof(char)*(strlen(server)+strlen("/tmp/.list")));
    sprintf(f, "/tmp/%s.list", server);
    write_on_file(f, msg);
    free(f);
}

void read_f(char* inf, int max_len, int fifo_fd, char* of, char mode, char* key, char* server ){
    FILE* stream = fopen(inf, "r");
    ssize_t read; 
    size_t len = max_len;
    char* line = NULL; char* tmp;

    while( (read = getline(&line, &len, stream) ) != -1 ){
        if( mode == 'e' ){
            tmp = encode( key, line );
            if( of == NULL )
                write_on_fifo( fifo_fd, tmp );
            else
                write_on_file( of, tmp );
            write_on_encoded_file( tmp, server );
        }else if( mode == 'd' ){
            tmp = decode( key, line );
            if( of == NULL )
                write_on_fifo( fifo_fd, tmp );
            else
                write_on_file( of, tmp );
        }else if( mode == 'l' ){
            if( of == NULL )
                write_on_fifo( fifo_fd, line );
            else
                write_on_file( of, line );
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
        perror(" Can not open response fifo: pthread -> client ");
        exit(-1);
    }
    return fifo;
}
