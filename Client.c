/********************************
*								*
*			AUTHORS				*
*								*
*********************************
Andrea Ghizzoni 157507
Federica Lago 157955
PROJECT: #1 CODEC
COURSE: Sistemi Operativi
YEAR: 2014
*/

#include <stdlib>
#include <include/client_args.h>

void set_values(Client_args* c, char* comand, char* value) {
	//foreach option
	if (strcmp(comand)=="-name") {
		setNameServer(c, value);
	}
	else if (strcmp(comand)=="-key") {
		setKey(c, value);
	}
	else if (strcmp(comand)=="-file") {
		setFileName(c, value);
		setisFile(c, 1);
	}
	else if (strcmp(comand)=="-message") {
		setMessage(value);
		setisFile(c, 0);
	}
	else if (strcmp(comand)=="-output") {
		setOutput(c, value);
	}
	else if (strcmp(comand)=="-encode") {
		setEncode(c,1);
	}
	else if (strcmp(comand)=="-decode") {
		setEncode(c, 0);
	}
}

void open_connection(Client_args* c) {
	if (c.nameServer!=NULL) {
		//cerco di aprire connessione col server, se non esiste errore
	}
	//invio tutti i parametri al server (c.key, c.isFile, c.fileName, c.message, c.output, c.encode)

}

int main(int argc, char** argv) {
	Client_args* c=malloc(sizeof (Client_args));
	c.nameServer=NULL;
	c.key=NULL;
	c.isFile=0;
	c.fileName=NULL;
	c.message=NULL;
	c.output=NULL;
	c.encode=1;

	int i=0;
	while (i<argc) {
		char* comand;
		char* value;
		comand=argv[i];
		i++;
		while ((i<argc)&&((*argv)[i][0]!="-")) {
			value=strcat(value, (*argv)[i]);
			i++;
		}
		set_values(comand, value);
	}

	open_connection(c);

	return 0;
}