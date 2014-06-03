#include <stdio.h>
#include <string.h>
#include "include/server.h"

int main(int argc, char** argv){
    char* msg = "34|e;lol|m;messaggio|o;\0";
    int len = strlen(msg);

    read_client_buffer(msg, len);
    return 0;
}
