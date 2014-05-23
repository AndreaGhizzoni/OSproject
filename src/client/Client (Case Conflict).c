/*
Andrea Ghizzoni 157507
Federica Lago 157955
PROJECT: #1 CODEC
COURSE: Sistemi Operativi
YEAR: 2014
*/

#include "include/client_args.h"
#include <stdio.h>

int main(int argc, char** argv) {
	Client_args* c =alloc();
	read_args(c, argc, argv);

	if ((nameServer==NULL)||((fileName==NULL)&&(message==NULL))||(op==NULL)) {
		return -1;
	}
	
	/*find_client(); -->inserisco l'id del server
	if (find_client(nameServer)==NULL)
		return -2;
	ask_server(nameServer, c);*/

	return 0;
}


