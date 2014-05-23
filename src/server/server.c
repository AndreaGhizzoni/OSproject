#include <stdio.h>
#include <stdlib.h>
#include "include/server_args.h"

int main(int argc, char** argv){
    Server_args* s = populate(argc, argv);
    if(s==NULL)
        exit(1);
    else
        print(s);
    return 0;
}

