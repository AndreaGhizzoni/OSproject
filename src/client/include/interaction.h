/* ============================== AUTHORS =====================================
# Andrea Ghizzoni 157507
# Federica Lago 157955
# PROJECT: #1 CODEC
# COURSE: Sistemi Operativi
# YEAR: 2014
=============================================================================*/

#ifndef INTERACION
#define INTERACION

/*Definizione errori*/
#define ERR_ARGUMENTS_MALFORMED -1
#define ERR_UNKNOWN_SERVER -2
#define ERR_UNABLE_TO_CONNECT -3

#include "include/client_args.h"

char* openClientFifo();

int findServer(char*);

void send_request(char*, char*);


#endif