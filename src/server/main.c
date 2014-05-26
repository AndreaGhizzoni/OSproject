#include <stdio.h>
#include <stdlib.h>
#include "include/server.h"

#define DEBUG 1

Server_args* parse_args(int, char**);

int main(int argc, char** argv){
    Server* server;
    if(DEBUG) printf("[!!!] SERVER IS RUNNING IN DEBUG MODE [!!!]\n");

    server = alloc_server();
    server->args = parse_args(argc, argv);
    server->fifo_path = set_fifo_path(server);

    return 0;
}

Server_args* parse_args(int argc, char** argv){
    Server_args* s = populate(argc, argv);
    if(s == NULL)
        exit(1);
   
    if(DEBUG) print(s);
    return s;
}

