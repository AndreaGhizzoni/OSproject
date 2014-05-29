/* ============================== AUTHORS =====================================
# Federica Lago 157955
# Andrea Ghizzoni 157507
# PROJECT: #1 CODEC
# COURSE: Sistemi Operativi
# YEAR: 2014
=============================================================================*/

#ifndef SERVER
#define SERVER

#include "server_args.h"

typedef struct {
    Server_args* args;
    char* fifo_path;

} Server;

/*Alloc the server structure space*/
Server* alloc_server();

/*set the default fifo path of each server*/
char* set_fifo_path(char*);

#endif
