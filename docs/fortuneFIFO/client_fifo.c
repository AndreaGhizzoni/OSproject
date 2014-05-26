#include <limits.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]) { 
	/* Variables definition */ 
	int n = 0; 
	char *fortunefilename; 
	char line[80]; 
	int fifo_server, fifo_client; 
	char fifoname[80]; 
	int nread; 
	char buffer[PIPE_BUF]; 

	sprintf(fortunefilename,"/tmp/fortune.fifo");
	snprintf(fifoname, 80, "/tmp/fortune.%d", getpid()); /* compose name */ 
	if (mkfifo(fifoname, 0622)) { /* open client fifo */ 
		if (errno!=EEXIST) { 
			perror("Cannot create well known fifo"); 
			exit(-1); 
	    } 
    } 
	
	fifo_server = open(fortunefilename, O_WRONLY); /* open server fifo */

	if (fifo_server < 0) { 
		perror("Cannot open well known fifo"); 
	    exit(-1); 
	} 
	nread = write(fifo_server, fifoname, strlen(fifoname)+1); /* write name */ 
	close(fifo_server);                     /* close server fifo */ 
	fifo_client = open(fifoname, O_RDONLY); /* open client fifo */ 
	if (fifo_client < 0) { 
		perror("Cannot open well known fifo"); 
		exit(-1); 
	} 
	nread = read(fifo_client, buffer, sizeof(buffer)); /* read answer */ 
	printf("%s", buffer);   /* print fortune */ 
	close(fifo_client);     /* close client */ 
	close(fifo_server);     /* close server */ 
	unlink(fifoname);       /* remove client fifo */ 
} 