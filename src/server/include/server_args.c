#include "server_args.h"
#include <stdlib.h>
#include <string.h>

Server_args* alloc(){
    Server_args* s = malloc( sizeof(Server_args) );
    s->name = NULL;
    s->msgmax = DEF_MSGMAX;
    s->keymin = DEF_KEYMIN;
    s->keymax = DEF_KEYMAX;
    return s;
}

int populate(Server_args* s, int argc, char** argv){
    if(s == NULL)
        s = alloc();

    for(int i=1; i<argc; i++){
        if(is_parameter(argv[i+1]) == 0)
            return ERR_ARGUMENT_MALFORMED;

        if(strcmp(argv[i], "-name") == 0){
            int r = set_name(s, argv[++i]);
            if(r != 0)
                return r;
        }
        
        if(strcmp(argv[i], "-msgmax") == 0){
            //TODO check if argv[++i] is a number
            int r = set_msgmax(s, atoi(argv[++i]));
            if(r != 0)
                return r;
        }

        if(strcmp(argv[i], "-keymin") == 0){
            //TODO check if argv[++i] is a number
            int r = set_keymin(s, atoi(argv[++i]));
            if(r != 0)
                return r;
        }

        if(strcmp(argv[i], "-keymax") == 0){
            //TODO check if argv[++i] is a number
            int r = set_keymax(s, atoi(argv[++i]));
            if(r != 0)
                return r;
        }
    }

    //if here s->name still == NULL, in args there isn't -name set
    if(s->name == NULL)
        return ERR_NAME_MISSING;

    return 0;
}

int set_name(Server_args* s, char* name){
    if(name == NULL)
        return ERR_NAME_NULL;
    if(name[0] == '-' )
        return ERR_NAME_MALFORMED;
    s->name = name;
    return 0;
}

int set_msgmax(Server_args* s, int msgmax){
    if(msgmax <= 0)
        return ERR_MSGMAX_MALFORMED;
    s->msgmax = msgmax;
    return 0;
}

int set_keymin(Server_args* s, int keymin){
    if(keymin <= 0 || keymin >= s->keymax)
        return ERR_KEYMIN_MALFORMED; 
    s->keymin = keymin;
    return 0;
}

int set_keymax(Server_args* s, int keymax){
    if(keymax <= 0 || keymax <= s->keymin)
        return ERR_KEYMAX_MALFORMED;
    s->keymax = keymax;
    return 0;
}

int is_parameter(char* s){
    if(s[0]=='-')
        return 0;
    else
        return -1;
}
