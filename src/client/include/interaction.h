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
/*Definizione errori*/
#define ERR_ARGUMENTS_MALFORMED -1
#define ERR_UNABLE_TO_CONNECT_TO_SERVER -2

/*Creates fifo for the client*/
char* createFifoClient();

/*Gets the name of the server's fifo using the server's name*/
char* getFifoServerName(char* name);

/*sends the client's request to server*/
int send_request(Client_args*);


#endif
