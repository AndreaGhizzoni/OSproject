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

/*this function read the char* given as a standard message from client
 * <pid>|<e/d/l>;<key>|<i/m>;<in_file/message>|o;<oit_file>\0*/
void read_client_buffer(char*, int); 

/*this function extracts the substring from message, from start to end point*/
char* substr(char*, int, int); 

#endif
