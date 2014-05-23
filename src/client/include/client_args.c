/*
Andrea Ghizzoni 157507
Federica Lago 157955
PROJECT: #1 CODEC
COURSE: Sistemi Operativi
YEAR: 2014
*/

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "client_args.h"

Client_args* alloc() {
	Client_args* c = (Client_args*) malloc( sizeof(Client_args) );
	c->nameServer=NULL;
	c->isFile=null;
	c->fileName=NULL;
	c->message=NULL;
	c->output=NULL;
	c->op=null;

	return c;	
}

void read_args(Client_args* c, int argc, char** argv) {
	int i=1;
	char* comand="";
	char* value="";
	while (i<argc) {
		comand=argv[i];
		printf("inside read_args %d\n", argc);
		i++;
		while ((i<argc)&&(argv[i][0]!='-')) {
			printf("inside read_args %s\n", argv[i]);
			strcat(value, argv[i]);	
			printf("inside while \n");
			i++;
		}
		printf("inside read_args %s\n", argv[i]);
		set_values(c, comand, value);
	}
}

int set_values(Client_args* c, char* comand, char* value) {
	printf("Inside set values %s\n", c->nameServer);
	if (strcmp(comand,"-name")==0) {
		setNameServer(c, value);
	}
	else if (strcmp(comand,"-key")==0) {
		setKey(c, value);
	}
	else if ((strcmp(comand,"-file")==0)&&(c->message==NULL)) {
		setFileName(c, value);
		setisFile(c, 1);
	}
	else if ((strcmp(comand,"-message")==0)&&(c->fileName==NULL)) {
		setMessage(c, value);
		setisFile(c, 0);
	}
	else if (strcmp(comand,"-output")==0) {
		setOutput(c, value);
	}
	else if ((strcmp(comand,"-encode")==0)&&(c->op==null)) {
		setOp(c,0);
	}
	else if ((strcmp(comand,"-decode")==0)&&(c->op==null)) {
		setOp(c, 1);
	}
	else if ((strcmp(comand,"-list")==0)&&(c->op==null)) {
		setOp(c, -1);
	}
	else return ERR_WRONG_ARGUMENTS;

	return 0;
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
	char* def = "test1"; /*TODO va cambiato */
	char* cn = malloc( sizeof(char)*(strlen(def)+strlen(OUTPUT_FILE)));
	if( value == NULL ) {
		strcat(cn, def );
		strcat(cn, OUTPUT_FILE);
		c->output=cn;
	}
	else {
		c->output=value;
	}
}

int setOp (Client_args* c, int value) {
	c->op=value;
	return 0;
}
