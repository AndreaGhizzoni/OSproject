/* ============================== AUTHORS =====================================
# Federica Lago 157955
# Andrea Ghizzoni 157507
# PROJECT: #1 CODEC
# COURSE: Sistemi Operativi
# YEAR: 2014
=============================================================================*/

#ifndef SERVER_ARGS
#define SERVER_ARGS

#define D_MSGMAX 100 /*default value of max message length*/
#define D_KEYMAX 100 /*default value of max key length*/
#define D_KEYMIN 1   /*default value of min key length*/

#define ERR_NAME_NULL -1
#define ERR_NAME_MISSING -7
#define ERR_NAME_MALFORMED -2
#define ERR_MSGMAX_MALFORMED -3
#define ERR_KEYMIN_MALFORMED -4
#define ERR_KEYMAX_MALFORMED -5
#define ERR_ARGUMENTS_MALFORMED -6

typedef struct {
    char* name; /*must to be set from sh*/
    int msgmax;
    int keymin;
    int keymax;
} Server_args;

/** 
 * Alloc a new type of Server_args
 */
Server_args* alloc();

/**
 * TODO modify docs
 * Populate a server_args given with the command line input in argv
 */
Server_args* populate(int, char**);

/**
 * return 0 if char* given is a command line argument, otherwise -1
 */
int is_parameter(char*);

/**
 * return -1 if char* is a invalid number, otherwise the atoi(char*) 
 */
int is_a_number(char*);

/**
 * Textual representation of type Server_args
 */
void print(Server_args*);

/**
 * Print the error just in case server arguments is like '--name --keymax 1 ..'
 */
void print_err(int*, char*, char*); 

/**
 * Print a description of server usage
 */
void print_usage();

#endif
