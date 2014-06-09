#ifndef CIPHER
#define CIPHER

/* this function take the key and returns a vector of int, as a pointer, with
 * the positions of each char of the key in the english alphabet */
int* intofkey( char* );

/* Encode the message with the key given */
char* encode( char*, char* ); 

/* Decode the message with the key given */
char* decode( char*, char* );

#endif
