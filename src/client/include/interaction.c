/* ============================== AUTHORS =====================================
# Andrea Ghizzoni 157507
# Federica Lago 157955
# PROJECT: #1 CODEC
# COURSE: Sistemi Operativi
# YEAR: 2014
=============================================================================*/

#include "interaction.h"
#include "client_args.h"
#include <stdio.h>

char* openClientFifo() {
	char* fifoname;
	snprintf(fifoname, 80, "/tmp/client.%d", getpid()); /* compose name */ 
	/* open client fifo */
	if (mkfifo(fifoname, 0622)) { 
		if (errno!=EEXIST) { 
			perror("Cannot create well known fifo"); 
			exit(-1); 
	    } 
    }
    return fifoname; 
}

int findServer(char* serverName) {
	char* serverFifoName = "/tmp/";
	strcat(serverFifoName, serverName);
	strcat(serverName, ".fifo");
	fifo_server = open(serverFifoName, O_WRONLY); /* open server fifo */
	if (fifo_server < 0) { 
		perror("Cannot open well known fifo"); 
	    return -1; 
	}	

	return 0;
} 

void send_request(client_args* c, char* fifo_client) {
	findServer(c->nameServer);
	int nread; 
	char buffer[PIPE_BUF];

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