/* ============================== AUTHORS =====================================
# Federica Lago 157955
# Andrea Ghizzoni 157507
# PROJECT: #1 CODEC
# COURSE: Sistemi Operativi
# YEAR: 2014
=============================================================================*/

#ifndef CLIENT_CARE
#define CLIENT_CARE

#include "server.h"

/*the handler function of pthread*/
void* pthread_handler(void*);

/*manage the comunicatione to the client according to parsed_msg passed*/
void manage_encodedecode(int, parsed_msg*, char);
void manage_list(int fifo_fd, parsed_msg* p);

/*write the char* to the fifo_fd passed as int*/
void write_on_fifo(int, char*);

/*char* file to read
 *int max length of file to read
 *int fifo_fd of client
 *char* output file
 *char 'e' || 'd' || 'l'
 *char* the key to encode or decode
 *char* the server name */
void read_f(char*, int, int, char*,char, char*, char*);

/*write a message given on file, first arg is message. second the file path*/
void write_on_file(char*, char*);

/*write the message on encoded server list.
 *first argument is the message
 *second is the server name*/
void write_on_encoded_file(char*, char*);

/*this function create the client fifo path from the char* of 
 * pid in /tmp/pid.fifo*/
char* fifo_client_path(char*);

/*this function returns the file identifier of client fifo*/
int open_fifo_client(char*);

#endif
