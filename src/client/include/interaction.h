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

/*Definizione errori*/
#define ERR_ARGUMENTS_MALFORMED -1
#define ERR_UNKNOWN_SERVER -2
#define ERR_UNABLE_TO_CONNECT -3

<<<<<<< HEAD
/*Contacts the server to perform the required operation*/
int call_server(Client_args*);
>>>>>>> 94ebabdd2e0d2fe79ddebbf5b7433dd447ea77f1

char* openClientFifo();

int findServer(char*);

void send_request(char*, char*);


#endif
