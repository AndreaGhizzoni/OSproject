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

#include <Client_args>
#include <ctype.c>

#define OUTPUT_FILE "_output.txt"

typedef struct{
    char* nameServer; 	//MANDATORY
    char* key;			//MANDATORY
    int isFile;
    char* fileName;
    char* message;
    char* output;
    int encode;			//MANDATORY
} Client_args;

/********************************
*								*
*			SETTERS				*
*								*
********************************/

void setName(Client_args* c, char* value) {
	c.name=value;
}

void setKey(Client_args* c, char* value) {
	int i=0;
	while ((*value)[i]) {
		if (!isalpha((*value)[i]))
			return;
		i++;
	}
	c.name=value;
}

void setisFile(Client_args* c, int isFile) {
	c.isFile=isFile;
}

void setFileName(Client_args* c, char* value) {
	c.name=value;
}

void setMessage(Client_args* c, char* value) {
	c.message=value;
}

void setOutput(Client_args* c, char* value) {
	if (value==NULL) {
		c.output=OUTPUT_FILE;
	}
	else {
		//controllo se è un nome di file valido
		c.output=value;
	}
}

int setEncode (Client_args* c, int value) {
	c.encode=value;
	return 0;
}
