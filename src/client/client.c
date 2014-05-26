/* ============================== AUTHORS =====================================
# Andrea Ghizzoni 157507
# Federica Lago 157955
# PROJECT: #1 CODEC
# COURSE: Sistemi Operativi
# YEAR: 2014
=============================================================================*/

#include "include/client_args.h"
#include "include/interaction.h"

int main(int argc, char** argv) {
	char* clientFifo;
	Client_args* c =populate(argc, argv);
    print(c);
    if (check_arguments(c) == -1)
    	return -1;

    clientFifo = createClientFifo();
    send_request(c);

	return 0;
}


