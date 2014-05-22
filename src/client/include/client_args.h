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

#ifndef CLIENT_ARGS
#define CLIENT_ARGS

#define OUTPUT_FILE "output.txt"

typedef struct{
    char* nameServer;
    int isFile;
    char* fileName;
    char* message;
    char* output;
    int op;
} Client_args;

Client_args* alloc();

/*Legge i parametri che il client riceve in ingresso*/
void read_args(Client_args*, int, char**);

/*Passa i parametri in ingresso alle opportune set*/
int set_values(Client_args*, char*, char*);

/*Setta il nome del server nella struct Client_args*/
void setNameServer(Client_args*, char*);

/*Setta la chiave nella struct Client_args*/
void setKey(Client_args*, char*);

/*Nella struct Client_args indica nel campo isFile
  se in ingresso c'è un file (isFile=1) oppure
  un messaggio di testo (isFile=0) */
void setisFile(Client_args*, int);

/*Setta il nome del file di input nella struct Client_args*/
void setFileName(Client_args*, char*);

/*Setta il messaggio nella struct Client_args*/
void setMessage(Client_args*, char*);

/*Setta il nome del file di output nella struct Client_args*/
void setOutput(Client_args*, char*);

/*Nella struct Client_args indica nel campo op
  se si vuole una codifica (op=0) oppure
  una decodifica (op=1) o una lista delle codifice
  avvenute su quel server (op=-1) */
int setOp (Client_args*, int);

#endif