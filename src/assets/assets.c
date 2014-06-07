#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MSG_L_MAX        10
#define N_ASSETS_FILES   10
#define N_MSG_FOR_ASSETS 7

char* rand_str(size_t);

int main(int argc, char** argv){
    FILE* tmp_f;
    int i=0; int j=0;
    char* n;

    srand(time(NULL));
    for(; i<N_ASSETS_FILES; i++ ){
        n = malloc( sizeof(char)*(strlen("../../assets/input_%d")));
        sprintf(n, "../../assets/input_%d", i);
        tmp_f = fopen( n, "ab+" );

        for(; j<N_MSG_FOR_ASSETS; j++)
            fprintf( tmp_f, "%s\n", rand_str( MSG_L_MAX ) );

        fflush(tmp_f);
        fclose(tmp_f);
        j=0;
    }

    return 0;
}

char* rand_str( size_t length ){
    char charset[] = "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* r = malloc( sizeof(char)*length+1 );
    size_t t;
    int i = 0;

    while( length-- > 0 ){
        t = rand() % strlen(charset);
        r[i++] = charset[t];
    }
    r[i+1] = '\0';

    return r;
}

