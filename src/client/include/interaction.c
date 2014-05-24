/* ============================== AUTHORS =====================================
# Andrea Ghizzoni 157507
# Federica Lago 157955
# PROJECT: #1 CODEC
# COURSE: Sistemi Operativi
# YEAR: 2014
=============================================================================*/

#include "interaction.h"
#include "client_args.h"
#include <stdio.h>

int call_server(Client_args* c) {
	if (find_server(c->nameServer)==-1) {
		printf("ERROR!! Unknown server. \n");
		return ERR_UNKNOWN_SERVER;
	}

	/*Passo parametri al server*/
	return 0;
}

int find_server(char* name) {
	/*if not found return -1*/
	return 0;
}