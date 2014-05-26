/* ============================== AUTHORS =====================================
# Andrea Ghizzoni 157507
# Federica Lago 157955
# PROJECT: #1 CODEC
# COURSE: Sistemi Operativi
# YEAR: 2014
=============================================================================*/

#include "interaction.h"
#include "client_args.h"
#include <limits.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

char* openClientFifo() {
	char* fifoname;
	sprintf(fifoname, "/tmp/client.%d", getpid()); /* compose name */ 
	/* open client fifo */
	if (mkfifo(fifoname, 0622)) { 
		if (errno!=EEXIST) { 
			perror("Cannot create well known fifo"); 
			exit(-1); 
	    } 
    }
    return fifoname; 
}

char* findServer(char* serverName) {
	char* serverFifoName = "/tmp/";
	int fifo_server;

	strcat(serverFifoName, serverName);
	strcat(serverName, ".fifo");
	
	fifo_server = open(serverFifoName, O_WRONLY); /* open server fifo */
	if (fifo_server < 0) { 
		perror("Cannot open well known fifo"); 
	    return NULL; 
	}	
	return serverFifoName;
} 

void send_request(Client_args* c, int fifo_client) {
	int nread; 
	char buffer[PIPE_BUF];
	int fifo_server;

	fifo_server=fifo_server(c->nameServer);
	if (fifo_server==NULL)
		return ERR_UNABLE_TO_CONNECT_TO_SERVER;

	/*send request to server*/
	nread = write(fifo_server, fifo_client, strlen(fifo_client)+1); /* write name */ 
	close(fifo_server);                     /* close server fifo */ 
	fifo_client = open(fifo_client, O_RDONLY); /* open client fifo */ 
	if (fifo_client < 0) { 
		perror("Cannot open well known fifo"); 
		exit(-1); 
	} 
	nread = read(fifo_client, buffer, sizeof(buffer)); /* read answer */ 
	printf("%s", buffer);   /* print fortune */ 
	close(fifo_client);     /* close client */ 
	close(fifo_server);     /* close server */ 
	unlink(fifo_client);    /* remove client fifo */ 
} 	