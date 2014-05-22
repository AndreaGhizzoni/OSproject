#include <stdio.h>
#include <stdlib.h>
#include "include/server_args.h"

void parse_args(int, char**);

int main(int argc, char** argv){

    return 0;
}

void parse_args(int argc, char** argv){
    int err;
    Server_args* sargs = alloc();
    err = populate( sargs, argc, argv );
    
}
