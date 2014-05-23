/* ============================== AUTHORS =====================================
# Andrea Ghizzoni 157507
# Federica Lago 157955
# PROJECT: #1 CODEC
# COURSE: Sistemi Operativi
# YEAR: 2014
=============================================================================*/

#include "client_args.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <getopt.h>
#include <ctype.h>

static struct option long_options[]={
    {"name"  , required_argument, 0, 'n'},
    {"key"  , required_argument, 0, 'k'},
    {"file", required_argument, 0, 'f'},
    {"message", required_argument, 0, 'm'},
    {"output", required_argument, 0, 'o'},
    {"encode", required_argument, 0, 'e'},
    {"decode", required_argument, 0, 'd'},
    {"list", required_argument, 0, 'l'},
    {0,0,0,0}
};
const char* shortopts = "n:kfmoedl";													/*IS IT RIGHT????????*/

Client_args* alloc() {
	Client_args* c = (Client_args*) malloc( sizeof(Client_args) );
	c->nameServer=NULL;
	c->key=NULL;
	c->isFile=D_INT_VALUE;
	c->fileName=NULL;
	c->message=NULL;
	c->output=NULL;
	c->op=D_INT_VALUE;

	return c;	
}

Client_args* populate(int argc, char** argv){
    int a, err;
    int option_index = 0; /*getopt_long stores the option index here. */
    Client_args* c;
    
    /*if argc == 1 means that --name||-n is missing*/
    if(argc==1){
        print_usage();
        return NULL;
    }

    c = alloc();
    err=0;

    while(1){
        a = getopt_long( argc, argv, shortopts, long_options, &option_index );

        if( a == -1 || err == -1 ) break;
        switch(a){
        	/*EDIT CASES*/
            case 'n':
                if(is_parameter(optarg) == 0 )
                    print_err(&err, "'--name'", "invalid");
                else
                    c->nameServer = optarg;
                break;

            case 'k':
                if((is_parameter(optarg) == 0 )||(checkKey(optarg) == -1))
                    print_err(&err, "'--key'", "invalid");
                else
                    c->key = optarg;
                break;

            case 'f':
                if((is_parameter(optarg) == 0 )||(c->message!=NULL))
                    print_err(&err, "'--file'", "invalid");
                else {
                    c->fileName = optarg;
                    c->isFile = 1;
                }
                break;

            case 'm':
                if((is_parameter(optarg) == 0 )||(c->fileName!=NULL))
                    print_err(&err, "'--message'", "invalid");
                else {
                    c->message = optarg;
                    c->isFile = 0;
                }
                break;

            case 'o':
                if(is_parameter(optarg) == 0 )
                	print_err(&err, "'--output'", "invalid");
                else	
                																	/*ADD setDefaultOutputFile(); */		
                    c->output = optarg;
                break;

            case 'e':
                if(is_parameter(optarg) == 0 )
                    print_err(&err, "'--encode'", "invalid");
                else
                    c->op = ENCODE;
                break;

            case 'd':
                if(is_parameter(optarg) == 0 )
                    print_err(&err, "'--decode'", "invalid");
                else
                    c->op = DECODE;
                break;

            case 'l':
                if(is_parameter(optarg) == 0 )
                    print_err(&err, "'--decode'", "invalid");
                else
                    c->op = LIST;
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
        return c;
}

int checkKey(char* key) {
	int i=0;
	while (key[i]) {
		if (!isalpha(key[i]))
			return -1;
		i++;
	}
	return 0;
}

void setDefaultOutputFile(Client_args* c) {
	char* def = "test1"; 													/*TODO va cambiato */
	char* cn = malloc( sizeof(char)*(strlen(def)+strlen(D_OUTPUT_FILE)));
	strcat(cn, def );
	strcat(cn, D_OUTPUT_FILE);
	c->output=cn;
}

int is_parameter(char* s){
    if(s[0]=='-')
        return 0;
    else
        return -1;
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

void print(Client_args* c){
    printf("Server arguments:\n");
    printf("-name: %s\n", c->nameServer);
    printf("-key: %s\n", c->key);
    printf("isFile: %d\n", c->isFile);
    printf("-file: %s\n", c->fileName);
    printf("-message: %s\n", c->message);
    printf("-output: %s\n", c->output);
    printf("operation: %d\n", c->op);
}