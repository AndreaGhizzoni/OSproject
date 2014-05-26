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

Server* alloc_server();
char* set_fifo_path(Server*);

#endif
