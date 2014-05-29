#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MSG_L_MAX        10
#define N_ASSETS_FILES   10
#define N_MSG_FOR_ASSETS 7
#define ASSEST_NAME      "../../assets/input_%d"

char* rand_str(size_t);

int main(int argc, char** argv){
    FILE* tmp_f;
    int i=0; int j=0;
    char* n;

    srand(time(NULL));
    for(; i<N_ASSETS_FILES; i++ ){
        n = malloc( sizeof(char)*(strlen(ASSEST_NAME)));
        sprintf(n, ASSEST_NAME, i);
        tmp_f = fopen( n, "a" );
        
        /* generate random string and write it in tmp_f */
        for(; j<N_MSG_FOR_ASSETS; j++)
            fprintf( tmp_f, "%s\n", rand_str( MSG_L_MAX ) );

        fflush(tmp_f);
        /* close tmp_f */
        fclose(tmp_f);
        j=0;
    }

    return 0;
}

char* rand_str( size_t length ){
    char charset[] = "0123456789"
                     "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* r = malloc( sizeof(char)*length );
    size_t t;
    int i = 0;

    while( length-- > 0 ){
        t = rand() % strlen(charset);
        r[i++] = charset[t];
    }
    r[i] = '\0';

    return r;
}

