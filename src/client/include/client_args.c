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
#include <unistd.h>

static struct option long_options[]={
    {"name"   , required_argument, 0, 'n'},
    {"key"    , required_argument, 0, 'k'},
    {"file"   , required_argument, 0, 'f'},
    {"message", required_argument, 0, 'm'},
    {"output" , optional_argument, NULL, 'o'},
    {"encode" , no_argument, 0, 'e'},
    {"decode" , no_argument, 0, 'd'},
    {"list"   , no_argument, 0, 'l'},
    {0,0,0,0}
};
const char* shortopts = "n:o::k:f:m:edl";

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
    
    /*if argc == 1 means that no argument passing*/
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
            case 'n':
                if(is_parameter(optarg) == 0)
                    print_err(&err, "'--name'", "is invalid");
                else
                    c->nameServer = optarg;
                break;

            case 'k':
                if(is_parameter(optarg) == 0)
                    print_err(&err, "'--key'", "is invalid");
                else if( check_key(optarg) == -1 )
                    print_err(&err, "'--key'", "can not contain numbers" );
                else
                    c->key = optarg;
                break;

            case 'f':
                if((is_parameter(optarg) == 0 )||(c->message!=NULL))
                    print_err(&err, "'--file'", "is invalid or '--message' is set");
                else {
                    c->fileName = optarg;
                    c->isFile = 1;
                }
                break;

            case 'm':
                if((is_parameter(optarg) == 0 )||(c->fileName!=NULL))
                    print_err(&err, "'--message'", "is invalid or '--file' is set");
                else {
                    c->message = optarg;
                    c->isFile = 0;
                }
                break;

            case 'o':
                if(!optarg)
                    set_default_outputFile(c);
                else
                    c->output = optarg;
                break;

            case 'e':
                if(c->op != D_INT_VALUE){
                    printf("error: '--encode' could not be set: '--decode' or '--list' is already set");
                    err=-1;
                }else{
                    c->op = ENCODE;
                }
                break;

            case 'd':
                if(c->op != D_INT_VALUE){
                    printf("error: '--decode' could not be set: '--encode' or '--list' is already set");
                    err=-1;
                }else{
                    c->op = DECODE;
                }
                break;

            case 'l':
                if(c->op != D_INT_VALUE){
                    printf("error: '--list' could not be set: '--encode' or '--decode' is already set");
                    err=-1;
                }else{
                    c->op = LIST;
                }
                break;

            case '?':
                err=-1;
                /*getopt_long already printed an error message.*/
                break;

            default:
                abort();
        }
    }

    if(err == -1 || check_arguments(c))
        return NULL;
    else
        return c;
}

int check_key(char* key) {
	int i=0;
	while(key[i]) {
		if (!isalpha(key[i]))
			return -1;
		i++;
	}
	return 0;
}

void set_default_outputFile(Client_args* c) {											
	char* cn = malloc( sizeof(char)*(strlen(D_OUTPUT_FILE)+6));
	sprintf(cn, "%d", getpid());
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
    printf("client --name severname [MODE] [INPUT] [OUTPUT]\n");
    printf("-n --name    : [MANDATORY] set the name of server to connect\n");
    printf("Mode:\n");
    printf("-e --encode  : encode mode, client send to server a message to encode\n");
    printf("-d --decode  : decode mode, client send to server a message to decode\n");
    printf("-l --list    : retrive from the server all messages encode/decode\n");
    printf("-k --key     : specify the key to encode/decode\n");
    printf("Input:\n");
    printf("-f --file    : specify the input file to get input message\n");
    printf("-m --message : specify the message to send to the server\n");
    printf("Output:\n");
    printf("-o --output  : specify if the output will be on file (--output file) or console (--output or not set)\n");
}

void print_err(int* err, char* from, char* msg){
    printf("error: value of %s: %s\n", from, msg);
    *err=-1;
}

void print(Client_args* c){
    printf("CLient arguments:\n");
    printf("--name: %s\n", c->nameServer);
    printf("--key: %s\n", c->key);
    printf("isFile: %d\n", c->isFile);
    printf("--file: %s\n", c->fileName);
    printf("--message: %s\n", c->message);
    printf("--output: %s\n", c->output);
    printf("operation: %d\n", c->op);
}

int check_arguments(Client_args* c) {
    if(c->nameServer == NULL){
        printf("error: argument missing '--name'\n");
        return -1;
    }

    if(c->op == D_INT_VALUE){
        printf("error: argument missing '--encode' || '--decode' || '--list'\n");
        return -1;
    }     

    if(c->op == ENCODE || c->op == DECODE ){
        if(c->key == NULL){
            printf("error: argument missing '--key'\n");
            return -1;
        }

        if(c->isFile == D_INT_VALUE){
            printf("error: argument missing '--file' || '--message'\n");
            return -1;
        }
    }
    
    return 0;
}
