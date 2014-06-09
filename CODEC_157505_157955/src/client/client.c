/* ============================== AUTHORS =====================================
# Andrea Ghizzoni 157507
# Federica Lago 157955
# PROJECT: #1 CODEC
# COURSE: Sistemi Operativi
# YEAR: 2014
=============================================================================*/

#include "include/client_args.h"
#include "include/interaction.h"
#include "../flags/flags.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	Client_args* c;
    if(DEB_CLIENT)printf("[!!!] CLIENT ID RUNNING IN DEBUG MODE [!!!]\n");

    c = populate(argc, argv);
    if( c == NULL )
        exit(1);
    else
        if(DEB_CLIENT)print(c);

    do_all(c);

	return 0;
}


