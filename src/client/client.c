/* ============================== AUTHORS =====================================
# Andrea Ghizzoni 157507
# Federica Lago 157955
# PROJECT: #1 CODEC
# COURSE: Sistemi Operativi
# YEAR: 2014
=============================================================================*/

#include "include/client_args.h"

int main(int argc, char** argv) {
	Client_args* c =populate(argc, argv);
    print(c);


	/*if ((c.nameServer==NULL)||((c.fileName==NULL)&&(c.message==NULL))||(c.op==NULL)) {
		return -1;
	}		TO FIX */
	
	/*find_client(); -->inserisco l'id del server
	if (find_client(nameServer)==NULL)
		return -2;
	ask_server(nameServer, c);*/

	return 0;
}


