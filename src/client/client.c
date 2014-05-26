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
	int fifo_client;
	Client_args* c =populate(argc, argv);
    print(c);

    fifo_client = createClientFifo();
    send_request(c, fifo_client);

	return 0;
}


