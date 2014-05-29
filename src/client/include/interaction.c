/* ============================== AUTHORS =====================================
# Andrea Ghizzoni 157507
# Federica Lago 157955
# PROJECT: #1 CODEC
# COURSE: Sistemi Operativi
# YEAR: 2014
=============================================================================*/

#include "client_args.h"
#include "interaction.h"
#include <limits.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

char* create_fifo_client() {
  char* fifoname = malloc( sizeof(char*)*(strlen("/tmp/client."))+6);    
  int pid_id = getpid();
  sprintf(fifoname, "/tmp/client.%d", pid_id);

  /* open client fifo */
  if (mkfifo(fifoname, 0622)) { 
    if (errno!=EEXIST) { 
      perror("Cannot create well known fifo"); 
      exit(-1); 
      } 
    }
  return fifoname;
}

char* get_fifo_server_name(char* name) {
  char* path = malloc( sizeof(char)*(strlen("/tmp/.fifo")+strlen(name)+1));
  sprintf(path, "/tmp/%s.fifo", name);
  return path;
}

char* format_buffer(Client_args* c) {
  char *pid, *mode, *input, *output, *msg;

  pid = malloc( sizeof(char)*6);
  sprintf(pid, "%d", getpid());

  if (c->op==-1) {
      mode = malloc( sizeof(char)*strlen("l;")+1);
  }
  else {                
    mode = malloc( sizeof(char)*(strlen(c->key)+3));
    if (c->op==0)
      sprintf(mode, "e;%s", c->key);
    else
      sprintf(mode, "d;%s", c->key);
  
    if (c->isFile==0) {
      input = malloc( sizeof(char)*(strlen(c->message)+3));
      sprintf(input, "m;%s", c->message);
    }
    else {
      input = malloc( sizeof(char)*(strlen(c->fileName)+3));
      sprintf(input, "i;%s", c->fileName);
    }

    if (c->output==NULL) {
      output = malloc( sizeof(char)*2);
      sprintf(output, ";");
    }
    else {
      output = malloc( sizeof(char)*(strlen(c->output)+3));
      sprintf(output, "o;%s", c->output);
    }
  }

  msg = malloc( sizeof(char)*(strlen(pid)+strlen(mode)+strlen(input)+strlen(output)+4));
  sprintf(msg, "%s|%s|%s|%s", pid, mode, input, output);

  return msg;
}

int send_request(Client_args* c) {
  /* Variables definition */
  int fifo_server, fifo_client, nread, size;
  char buffer[PIPE_BUF];
  char* message;
  char* fifoname = create_fifo_client();
  char *nameFifoServer = get_fifo_server_name(c->nameServer);
  
  /* open server fifo */
  fifo_server = open(nameFifoServer, O_WRONLY);
  if (fifo_server < 0) { 
    perror("Cannot open well known fifo"); 
      exit(-1); 
  }

  /*write request*/
  message=format_buffer(c);
  size= sizeof(char)*strlen(message);
  sprintf(buffer, "%d", size);
  nread = write(fifo_server, buffer, strlen(fifoname)+1);
  sprintf(buffer, "%s", message);
  close(fifo_server);

  /*open client's fifo in read mode*/
  fifo_client = open(fifoname, O_RDONLY);
  if (fifo_client < 0) { 
    perror("Cannot open well known fifo"); 
    exit(-1); 
  }

  /*loop to chack when the client can read*/

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