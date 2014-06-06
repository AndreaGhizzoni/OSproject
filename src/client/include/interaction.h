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
#define D_OUTPUT_FILE "output.txt"

#define PIPE_BUF 4096
/*Definizione errori*/
#define ERR_ARGUMENTS_MALFORMED -1
#define ERR_UNABLE_TO_CONNECT_TO_SERVER -2

char* create_fifo_client();

char* get_fifo_server_name(char*);

int get_fifo_server(char*);

int get_fifo_client(char*);

char* format_buffer(Client_args*);

void read_answer(int, char*);

void send_request(Client_args*, int);

int handle_request(Client_args*);

#endif
