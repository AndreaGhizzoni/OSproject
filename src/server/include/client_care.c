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
#include "client_care.h"
#include "server.h"

void* pthread_handler(void* p_m){
    /*struct parsed_msg* p_msg = p_m;*/


    return NULL;
}

void write_on_list(char* msg, char* output_file){
    FILE* stream = fopen(output_file, "a");
    fputs(msg, stream);
    fputs("\n", stream);
    fflush(stream);
    fclose(stream);
}

void read_on_list(char* output_file, char* server_name, int max_len){
    FILE* stream = fopen(output_file, "r");
    ssize_t read; /*this will be the lien length*/
    size_t len = max_len;
    char* line = NULL;

    /*TODO not print but send it to client*/
    while( (read = getline(&line, &len, stream) ) != -1 ){
        printf("%s", line);
    }
    /*sand to the client a list terimaton*/

    fflush(stream);
    fclose(stream);
}
