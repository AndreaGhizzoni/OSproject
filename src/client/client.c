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

	printf("server name %s\n", c->nameServer);
	printf("server name %d\n", c->isFile);
	printf("server name %s\n", c->fileName);
	printf("server name %s\n", c->message);
	printf("server name %s\n", c->output);
	printf("server name %d\n", c->op);


	/*if ((c.nameServer==NULL)||((c.fileName==NULL)&&(c.message==NULL))||(c.op==NULL)) {
		return -1;
	}		TO FIX */
	
	/*find_client(); -->inserisco l'id del server
	if (find_client(nameServer)==NULL)
		return -2;
	ask_server(nameServer, c);*/

	return 0;
}


