/* ============================== AUTHORS =====================================
# Federica Lago 157955
# Andrea Ghizzoni 157507
# PROJECT: #1 CODEC
# COURSE: Sistemi Operativi
# YEAR: 2014
=============================================================================*/

#include "server_args.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <getopt.h>

Server_args* alloc_args(){
    Server_args* s = malloc( sizeof(Server_args) );
    s->name = NULL;
    s->msgmax = D_MSGMAX;
    s->keymin = D_KEYMIN;
    s->keymax = D_KEYMAX;
    return s;
}

static struct option long_options[]={
    {"name"  , required_argument, 0, 'n'},
    {"keymax", required_argument, 0, 'K'},
    {"keymin", required_argument, 0, 'k'},
    {"msgmax", required_argument, 0, 'M'},
    {0,0,0,0}
};
const char* shortopts = "n:kKM";

Server_args* populate(int argc, char** argv){
    int c, keymin, keymax, msgmax, err;
    int option_index = 0; /*getopt_long stores the option index here. */
    Server_args* s;
    
    /*if argc == 1 means that --name||-n is missing*/
    if(argc==1){
        print_usage();
        return NULL;
    }

    s = alloc_args();
    err=0;

    while(1){
        c = getopt_long( argc, argv, shortopts, long_options, &option_index );

        if( c == -1 || err == -1 ) break;

        switch(c){
            case 'n':
                if(is_parameter(optarg) == 0 )
                    print_err(&err, "'--name'", "invalid");
                else
                    s->name = optarg;
                break;
            case 'K':
                if(is_parameter(optarg) == 0 ||
                  ((keymax = is_a_number(optarg)) == -1 ))
                    print_err(&err, "'--keymax'", "invalid");
                else
                    s->keymax = keymax;
                break;
            case 'k':
                if(is_parameter(optarg) == 0 || 
                  ((keymin = is_a_number(optarg)) == -1 ))
                    print_err(&err, "'--keymin'", "invalid");
                else
                    s->keymin = keymin;
                break;
            case 'M':
                if(is_parameter(optarg) == 0 ||
                  ((msgmax = is_a_number(optarg)) == -1 ))
                    print_err(&err, "'--msgmax'", "invalid");
                else
                    s->msgmax = msgmax;
                break;

            case '?':
                err=-1;
                /*getopt_long already printed an error message.*/
                break;

            default:
                abort();
        }
    }

    if(err == -1)
        return NULL;
    else
        return s;
}

int is_parameter(char* s){
    if(s[0]=='-')
        return 0;
    else
        return -1;
}

int is_a_number(char* s){
    int num = atoi(s);
    if (num == 0 && s[0] != '0')
       return -1; 
    else
       return num;
}

void print_usage(){
    printf("server --name string [--msgmax int] [--keymin int] [--keymax int]\n");
    printf("-n --name : [MANDATORY] specify the name of the service\n");
    printf("-K --keymax : specify the max length of the key that server can recive\n");
    printf("-k --keymin : specify the min length of the key that server can recive\n");
    printf("-M --msgmax : specify the max length of the message that server can recive\n");
}

void print_err(int* err, char* from, char* msg){
    printf("error: value of %s is %s\n", from, msg);
    *err=-1;
}

void print(Server_args* s){
    printf("Server arguments:\n");
    printf("--name: %s\n", s->name);
    printf("--msgmax: %d\n", s->msgmax);
    printf("--keymin: %d\n", s->keymin);
    printf("--keymax: %d\n", s->keymax);
}


