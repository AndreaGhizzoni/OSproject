#include <stdio.h>
#include <stdlib.h>
#include "include/server_args.h"

Server_args* parse_args(int, char**);

int main(int argc, char** argv){
    Server_args* s;
    s = parse_args(argc, argv);
    if(s!=NULL)
        print(s);
    

    return 0;
}

Server_args* parse_args(int argc, char** argv){
    int err;
    Server_args* sargs = alloc();
    err = populate(sargs, argc, argv);
    if(err==0)
        return sargs;
    
    printf("%d\n",err);
    return NULL;
}
