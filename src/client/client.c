/********************************
*								*
*			AUTHORS				*
*								*
*********************************
Andrea Ghizzoni 157507
Federica Lago 157955
PROJECT: #1 CODEC
COURSE: Sistemi Operativi
YEAR: 2014
*/

#include "include/client_args.h"
#include <stdio.h>

/********************************
*								*
*			  MAIN				*
*								*
*********************************/

int main(int argc, char** argv) {
	Client_args* c =alloc();
	read_args(c, argc, argv);

	printf ("server name: %s \n", c->nameServer);
	printf ("server name: %c \n", c->isFile);
	printf ("server name: %s \n", c->fileName);
	printf ("server name: %s \n", c->message);
	printf ("server name: %s \n", c->output);
	printf ("server name: %c \n", c->op);

	/*if the server exits i ask it to encode/decode/print
	if output=file then i put i write it on the file*/

	return 0;
}