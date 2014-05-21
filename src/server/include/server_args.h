#ifndef SERVER_ARGS
#define SERVER_ARGS

#include <stdio.h>

#define DEF_MSGMAX 100 //default value of max message length
#define DEF_KEYMAX 100 //default value of max key length
#define DEF_KEYMIN 1   //default value of min key length

#define ERR_NAME_NULL -1
#define ERR_NAME_MISSING -7
#define ERR_NAME_MALFORMED -2
#define ERR_MSGMAX_MALFORMED -3
#define ERR_KEYMIN_MALFORMED -4
#define ERR_KEYMAX_MALFORMED -5
#define ERR_ARGUMENT_MALFORMED -6

typedef struct{
    char* name; //must to be set from sh
    int msgmax;
    int keymin;
    int keymax;
} Server_args;

/** 
 * Alloc a new type of Server_args
 */
Server_args* alloc();

/**
 * Populate a server_args given with the command line input in argv
 */
int populate(Server_args*, int, char**);

/**
 * Set the name of server_args with the char* given
 */
int set_name(Server_args*, char*);

/**
 * Set the max length of message that server can recive
 */
int set_msgmax(Server_args*, int);

/**
 * Set the minimum length of key that server can recive
 */
int set_keymin(Server_args*, int);

/**
 * Set the name of server_args with the char* given
 */
int set_keymax(Server_args*, int);

/**
 * Set the name of server_args with the char* given
 */
int is_parameter(char*);

#endif
