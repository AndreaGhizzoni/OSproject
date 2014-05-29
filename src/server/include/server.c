/* ============================== AUTHORS =====================================
# Federica Lago 157955
# Andrea Ghizzoni 157507
# PROJECT: #1 CODEC
# COURSE: Sistemi Operativi
# YEAR: 2014
=============================================================================*/

#include "server.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

Server* alloc_server(){
    Server* s = malloc( sizeof(Server) );
    s->args = NULL;
    s->fifo_path = NULL;
    return s;
}

char* set_fifo_path(char* s){
    char* fifo;
    int c;
    if(s== NULL)
        return NULL;
    
    c = strlen(s)+strlen("/tmp/.fifo");
    fifo = malloc(sizeof(char)*c);
    sprintf(fifo, "/tmp/%s.fifo", s);

    return fifo;    
}
