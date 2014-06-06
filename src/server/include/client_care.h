/* ============================== AUTHORS =====================================
# Federica Lago 157955
# Andrea Ghizzoni 157507
# PROJECT: #1 CODEC
# COURSE: Sistemi Operativi
# YEAR: 2014
=============================================================================*/

#ifndef CLIENT_CARE
#define CLIENT_CARE

void* pthread_handler(void*);

/*write a message given on the server encoded list*/
void write_on_list(char*, char*);

/*read all the content of server encoded message file*/
void read_on_list(char*, char*, int);

#endif
