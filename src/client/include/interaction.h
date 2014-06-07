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

char* fifo_server_path(char*);
int open_fifo_server(char*);

char* fifo_client_path(int);
int open_fifo_client(char*);

char* format_buffer(Client_args*);

void send_request(Client_args*, int);
void read_response(int);

void do_all(Client_args*);

#endif
