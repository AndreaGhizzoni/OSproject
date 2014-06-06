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

int get_fifo_server(char* nameFifoServer) {
  int fifo_server = open(nameFifoServer, O_WRONLY);
  if (fifo_server < 0) { 
    perror("Cannot open well known fifo"); 
      exit(-1); 
  }
  return fifo_server;
}

int get_fifo_client(char* fifoname) {
  int fifo_client = open(fifoname, O_RDONLY);
  if (fifo_client < 0) { 
    perror("Cannot open well known fifo"); 
    exit(-1); 
  }
  return fifo_client;
}

char* format_buffer(Client_args* c) {
  char *pid, *mode, *input, *output, *msg;
  int lenall;

  pid = malloc( sizeof(char)*6);
  sprintf(pid, "%d", getpid());

  if (c->op==-1) {
      mode = malloc( sizeof(char)*strlen("l;")+1);
      sprintf(mode, "l;");
      lenall = strlen(pid)+ strlen(mode)+3;
      msg = malloc( sizeof(char)*lenall );
      sprintf(msg, "%s|%s||", pid, mode);
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

    lenall = strlen(pid)+strlen(mode)+strlen(input)+strlen(output)+4;
    msg = malloc( sizeof(char)*lenall );
    sprintf(msg, "%s|%s|%s|%s", pid, mode, input, output);
  }
  return msg;
}

void read_answer(int fifo_client, char* fifoname) {
    /*
  int nread;
  char buffer[PIPE_BUF];

  printf("Waiting for answer...\n");
  nread = read(fifo_client, buffer, sizeof(buffer));
  while (nread==0) {
    nread = read(fifo_client, buffer, sizeof(buffer));
  }

  if (strcmp(buffer, "OK")!=0 && strcmp(buffer, "ERR")!=0) {
    nread = read(fifo_client, buffer, sizeof(buffer));
    printf("%s%d", buffer, nread);
  }
  */
}

void send_request(Client_args* c, int fifo_server) {
  char* message;
  char buffer[PIPE_BUF];
  int msg_size, nread;

  /*write request*/
  message = format_buffer(c);
  msg_size = sizeof(char)*strlen(message);

  sprintf(buffer, "%d", msg_size);
  nread = write(fifo_server, buffer, 4);
  if( nread == -1 ){
    printf("error first nread" );
    exit(1);
  }

  sprintf(buffer, "%s", message);
  nread = write(fifo_server, buffer, msg_size); 
  if( nread == -1 ){
      printf("error second nread" );
      exit(1);
  }
}

int handle_request(Client_args* c) {
  int fifo_server = get_fifo_server(get_fifo_server_name(c->nameServer));
  send_request(c, fifo_server);
  close(fifo_server);
  return 0;
}   
