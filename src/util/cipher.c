#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "cipher.h"

char* encode(char* key, char* message) {
    int len = strlen( key );
	int* int_of_key = intofkey( key );
    char* encode_msg = malloc( sizeof(char)*len+1 );

	int i=0; int j=0; int tmp=0;
	while( message[i] != '\0' ) {
        if( message[i] == '\n'){i++; continue;}
		/*se la lettera corrente è maiuscola la porto temporaneamente in 
        minuscolo sottraggo 'a' per avere la posizione nell'alfabeto,
		sommo la posizione corrente della chiave e sottraggo 
        26 se sono oltre la z*/
		if( isalpha(message[i]) ) {
			if( isupper( message[i] ) ) {
				tmp = tolower( message[i] )-'a';
				tmp += int_of_key[j];
				if( tmp>25 )
					tmp-=26;
				encode_msg[i] = toupper( tmp+'a' );
		    }else{
				tmp = message[i]-'a';
				tmp += int_of_key[j];
				if( tmp>25 )
					tmp-=26;
				encode_msg[i] = tmp+'a';
			}
			
			if( j < len-1 )
				j++;
			else
				j=0;
		}
		i++;
	}

    encode_msg[len+1] = '\0';
    return encode_msg;
}

char* decode(char* key, char* message ){
	int len = strlen( key );
	int* int_of_key = intofkey( key );
    char* decoded_msg = malloc( sizeof(char)*len+1 );

	int i=0; int j=0; int tmp=0;
	while( message[i] != '\0' ) {
        if( message[i] == '\n'){i++; continue;}
		/*se la lettera corrente è maiuscola la porto temporaneamente in 
        minuscolo sottraggo 'a' per avere la posizione nell'alfabeto,
		sottraggo la posizione corrente della chiave e sommo 26 
        se sono prima della a*/
		if( isalpha( message[i]) ){
			if( isupper( message[i] ) ){
				tmp = tolower( message[i] )-'a';
				tmp -= int_of_key[j];
				if( tmp<0 )
					tmp+=26;
				decoded_msg[i] = toupper( tmp+'a' );
			}
			else {
				tmp = message[i]-'a';
				tmp -= int_of_key[j];
				if( tmp<0 )
					tmp+=26;
				decoded_msg[i] = tmp+'a';
			}
			
			if (j<len-1)
				j++;
			else
				j=0;
		}
		i++;
	}

    decoded_msg[len+1] = '\0';
    return decoded_msg;
}

int* intofkey( char* key ) {
    int len = strlen( key );
    int* r = malloc( sizeof(int)*len );
	int i=0;
	while( key[i] != '\0' ){
        if( isupper( key[i] ) ) 
            r[i] = tolower(key[i])-'a'+1;
        else
            r[i] = key[i]-'a'+1;
        i++;
    }	
    return r;
}


