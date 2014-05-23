/* ============================== AUTHORS =====================================
# Andrea Ghizzoni 157507
# Federica Lago 157955
# PROJECT: #1 CODEC
# COURSE: Sistemi Operativi
# YEAR: 2014
=============================================================================*/

#ifndef CLIENT_ARGS
#define CLIENT_ARGS

/*Definizione errori*/
#define ERR_NAME_NULL -1
#define ERR_NAME_MISSING -7
#define ERR_NAME_MALFORMED -2
#define ERR_MSGMAX_MALFORMED -3
#define ERR_KEYMIN_MALFORMED -4
#define ERR_KEYMAX_MALFORMED -5
#define ERR_ARGUMENTS_MALFORMED -6

/*Definizione variabili*/
#define D_OUTPUT_FILE "output.txt"
#define D_INT_VALUE -2
#define ENCODE 0
#define DECODE 1
#define LIST -1

typedef struct{
    char* nameServer; /*must be setted*/
    char* key; /*must be setted if op>=0 */
    int isFile; 
    char* fileName;
    char* message;
    char* output;
    int op;  /*must be !=-2 */
} Client_args;


/*Alloca la struttura Client_args*/
Client_args* alloc();

/**
 * TODO modify docs
 * Populate a server_args given with the command line input in argv
 */
Client_args* populate(int, char**);

/*Checks if char* is a valid key, only made of letters*/
int checkKey(char*);

/*Sets the default name for the output file*/
void setDefaultOutputFile(Client_args*);

/*return 0 if char* given is a command line argument, otherwise -1 */
int is_parameter(char*);


/*Print a description of server usage */
void print_usage();

/*Print the error just in case server arguments is like '--name --keymax 1 ..' */
void print_err(int*, char*, char*); 

/*Textual representation of type Client_args*/
void print(Client_args*);

#endif











