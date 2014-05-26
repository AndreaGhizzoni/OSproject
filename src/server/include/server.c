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

Server* alloc_server(){
    Server* s = malloc( sizeof(Server) );
    s->args = NULL;
    s->fifo_path = NULL;
    return s;
}

char* set_fifo_path(Server* s){
    char* fifo;
    if(s->args == NULL)
        return NULL;

    fifo = malloc(strlen(s->args->name)+strlen("/tmp/.fifo"));
    sprintf(fifo, "/tmp/%s.fifo", s->args->name);

    return fifo;    
}
