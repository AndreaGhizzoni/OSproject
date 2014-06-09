/* ============================== AUTHORS =====================================
# Federica Lago 157955
# Andrea Ghizzoni 157507
# PROJECT: #1 CODEC
# COURSE: Sistemi Operativi
# YEAR: 2014
=============================================================================*/

#ifndef SERVER
#define SERVER

#include "server_args.h"

typedef struct {
    Server_args* args;
    char* fifo_path;
    char* encoded_file_path;

} Server;

typedef struct {
    char* pid;        /*NULL: not set*/
    char* server_name;/*NULL: not set, necessary to write encoded msg to server file*/
    char what_to_do;  /*x: not set, e: encode, d: decode, l: list*/
    char i_mode;      /*x: not set, i: input file, m: message*/
    char o_mode;      /*x: not set, o: output file, c: console*/

    char* key;     /*not NULL if what_to_do=='e' || what_to_do=='d'*/
    char* in_file; /*not NULL if i_mode=='i'*/
    char* in_msg;  /*not NULL if i_mode=='m'*/
    char* out_file;/*not NULL if o_mode=='o'*/

    char*  error; /*not NULL if there was some errors*/
} parsed_msg;

/*Alloc the server structure space*/
Server* alloc_server();

/*Alloc the parsed client message space*/
parsed_msg* alloc_parsed_msg();

/*set the default fifo path of each server*/
char* set_fifo_path(char*);

/*this methdo returns the server encoded list as char*. 
 *if doesn't exists it will be create */
char* set_encoded_file(char*);

/*this function read the char* given as a standard message from client
 * <pid>|<e/d/l>;<key>|<i/m>;<in_file/message>|o;<oit_file>\0*/
parsed_msg* read_client_buffer(char*, char*); 

/*this function check if pid passed as char* is a valid number*/
void parse_pid(parsed_msg*, char*);

/*this function parse the char* passed as the part of client message about
 * what server will do*/
void parse_mode(parsed_msg*, char*);

/*this function parse the char* passed as the part of client message about 
 * the input menthod of message to decode/encode*/
void parse_input(parsed_msg*, char*);

/*this function parse the char* passed as the part of client message about
 * the output method of the server*/
void parse_output(parsed_msg*, char*);

/*this function extracts the substring from message, from start to end point*/
char* substr(char*, int, int); 

/*you know what this function does*/
void print_parsed_msg(parsed_msg*);
#endif
