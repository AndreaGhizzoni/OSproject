/* ============================== AUTHORS =====================================
# Andrea Ghizzoni 157507
# Federica Lago 157955
# PROJECT: #1 CODEC
# COURSE: Sistemi Operativi
# YEAR: 2014
=============================================================================*/

#include "include/client_args.h"
#include "include/interaction.h"

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

int main(int argc, char** argv) {
<<<<<<< HEAD
	Client_args* c;
    if(DEBUG) printf("[!!!] CLIENT ID RUNNING IN DEBUG MODE [!!!]\n");

    c = populate(argc, argv);
    if( c == NULL )
        exit(1);
    else
        print(c);
>>>>>>> 94ebabdd2e0d2fe79ddebbf5b7433dd447ea77f1

	return 0;
}


