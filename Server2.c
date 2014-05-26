void openServerFifo(char* name) {
	char* fifoname="/tmp/";
	strcat(fifoname, name);
	strcat(fifoname, ".fifo");

	Signal ( SIGTERM , HandSIGTERM ); /* set handlers for termination */
	Signal ( SIGINT , HandSIGTERM );
	Signal ( SIGQUIT , HandSIGTERM );

	if ( mkfifo ( fifoname , 0622)) { /* create well known fifo if does ’t exist */
		if ( errno != EEXIST ) {
			perror ( " Cannot create well known fifo " );
			exit (1);
		}
	}

	daemon (0, 0);

	/* open fifo two times to avoid EOF */
	fifo_server = open ( fifoname , O_RDONLY );
	if ( fifo_server < 0) {
		perror ( " Cannot open read only well known fifo " );
		exit (1);
	}

	if ( open ( fifoname , O_WRONLY ) < 0) {
		perror ( " Cannot open write only well known fifo " );
		exit (1);
	}
}

void answer_request(char* fifo_client, char* fifo_server) {
	int nread;
	char line [80];

	while (1) {
		nread = read ( fifo_server , line , 79); /* read request */
		if ( nread < 0) {
			perror ( " Read Error " );
			exit (1);
		}

		line [ nread ] = 0; /* terminate fifo name string */
		fifo_client = open ( line , O_WRONLY ); /* open client fifo */

		if ( fifo_client < 0) {
			perror ( " Cannot open " );
			exit (1);
		}

		nread = write ( fifo_client);	 								/* TO DO edit */
		close ( fifo_client ); /* close client fifo */
	}
}



