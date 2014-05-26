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

/*Contacts the server to perform the required operation*/
int call_server(Client_args*);

/*Checks if the server exists*/
int find_server(char*);


#endif
