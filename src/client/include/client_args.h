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

#ifndef CLIENT_ARGS
#define CLIENT_ARGS
#endif

#include <ctype.c>

#define OUTPUT_FILE "output.txt"

typedef struct{
    char* nameServer; 	//MANDATORY
    char* key;			//MANDATORY
    int isFile;
    char* fileName;
    char* message;
    char* output;
    int encode;			//MANDATORY
} Client_args;

Client_args* alloc();

/********************************
*								*
*			SETTERS				*
*								*
********************************/

void setName(Client_args*, char*);

void setKey(Client_args*, char*);

void setisFile(Client_args*, int);

void setFileName(Client_args*, char*);

void setMessage(Client_args*, char*);

void setOutput(Client_args*, char*);

int setEncode (Client_args*, int);
