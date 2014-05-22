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

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "client_args.h"

Client_args* alloc() {
	Client_args* c = (Client_args*) malloc( sizeof(Client_args) );
	return c;	
}

void read_args(Client_args* c, int argc, char** argv) {
	int i=1;
	char* comand;
	char* value;
	while (i<argc) {
		comand=argv[i];
		i++;
		while ((i<argc)&&(argv[i][0]!='-')) {
			value=strcat(value, argv[i]);							
			i++;
		}
		set_values(c, comand, value);
	}
}

void setNameServer(Client_args* c, char* value) {
	c->nameServer=value;
}

void setKey(Client_args* c, char* value) {
	int i=0;
	while (value[i]) {
		if (!isalpha(value[i]))
			return;
		i++;
	}
	c->nameServer=value;
}

void setisFile(Client_args* c, int isFile) {
	c->isFile=isFile;
}

void setFileName(Client_args* c, char* value) {
	c->fileName=value;
}

void setMessage(Client_args* c, char* value) {
	c->message=value;
}

void setOutput(Client_args* c, char* value) {
	char* clientName;
	if (!value) {
		clientName=strcat(clientName, OUTPUT_FILE);
		c->output=clientName;
	}
	else {
		c->output=value;
	}
}

int setOp (Client_args* c, int value) {
	c->op=value;
	return 0;
}

int set_values(Client_args* c, char* comand, char* value) {
	if (strcmp(comand,"-name")==0) {
		setNameServer(c, value);
	}
	else if (strcmp(comand,"-key")==0) {
		setKey(c, value);
	}
	else if (strcmp(comand,"-file")==0) {
		setFileName(c, value);
		setisFile(c, 1);
	}
	else if (strcmp(comand,"-message")==0) {
		setMessage(c, value);
		setisFile(c, 0);
	}
	else if (strcmp(comand,"-output")==0) {
		setOutput(c, value);
	}
	else if (strcmp(comand,"-encode")==0) {
		setOp(c,0);
	}
	else if (strcmp(comand,"-decode")==0) {
		setOp(c, 1);
	}
	else if (strcmp(comand,"-list")==0) {
		setOp(c, -1);
	}
	else return -1;

	return 0;
}
