/* ============================== AUTHORS =====================================
# Andrea Ghizzoni 157507
# Federica Lago 157955
# PROJECT: #1 CODEC
# COURSE: Sistemi Operativi
# YEAR: 2014
=============================================================================*/

#ifndef INTERACION
#define INTERACION

#include "client_args.h"

#define PIPE_BUF 4096
/*this function returns the fifo server path from server name given as char* */
char* fifo_server_path(char*);
/*this function open the server fifo from the path given as char* */
int open_fifo_server(char*);

/*this function returns the fifo client path from the pid of client as int*/
char* fifo_client_path(int);
/*this function open the client fifo from the path given as char* */
int open_fifo_client(char*);

/*this function create a string with all data that server need
 *char* format: see src/server/include/server.c:read_client_buffer(char*, char*)*/
char* format_buffer(Client_args*);

/*this function send the first request to server. 
 *second argument is the fifo server descriptor*/
void send_request(Client_args*, int);
/*this function read the response from the server fifo passed as int file descriptor*/
void read_response(int);

/*call all the functions above*/
void do_all(Client_args*);

#endif
