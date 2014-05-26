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

char* createFifoClient() {
	char* fifoname="";

	sprintf(fifoname, "/tmp/client.%d", getpid()); /* compose name */ 
	if (mkfifo(fifoname, 0622)) { /* open client fifo */ 
		if (errno!=EEXIST) { 
			perror("Cannot create well known fifo"); 
			exit(-1); 
	    } 
    } 
	return fifoname;
}

char* getFifoServerName(char* name) {
	char* path="";
	sprintf(path, "/tmp/%s.fifo", name);
	return path;
}

int send_request(Client_args* c) {
	/* Variables definition */  
	char* nameFifoServer; 
	int fifo_server, fifo_client, nread; 
	char* fifoname;
	char buffer[PIPE_BUF]; 

	fifoname = createFifoClient();
	nameFifoServer = getFifoServerName(c->nameServer);
	
	/* open server fifo */
	fifo_server = open(nameFifoServer, O_WRONLY);
	if (fifo_server < 0) { 
		perror("Cannot open well known fifo"); 
	    exit(-1); 
	} 

	/*write request*/
	nread = write(fifo_server, buffer, strlen(fifoname)+1);
	close(fifo_server);

	/*open client's fifo in read mode*/
	fifo_client = open(fifoname, O_RDONLY);
	if (fifo_client < 0) { 
		perror("Cannot open well known fifo"); 
		exit(-1); 
	} 
	/* read answer */ 
	nread = read(fifo_client, buffer, sizeof(buffer));

	/*print answer*/
	printf("%s%d", buffer, nread);

	/*Close fifos and remove client fifo*/
	close(fifo_client);
	close(fifo_server);
	unlink(fifoname);

	return 0;
} 	