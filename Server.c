using namespace std;

#include <iostream>
#include <ctype.h>
#include <string.h>

/* in c metto le posizioni nell'alfabeto
 di ciascuna lettera (minuscola) che compone la chiave*/
void convertkey(int *c, char chiave[]) {
	int i=0;
	while (chiave[i]) {
        if (isupper(chiave[i])) {
        	chiave[i] =tolower(chiave[i]);
        }
        c[i]=chiave[i]-'a'+1;
        i++;
    }	
}

/*funzione che codifica il messaggio*/
void encode(char chiave[], char message[]) {
	int len=strlen(chiave);
	int c[len];
	convertkey(c, chiave);

	//inizio la codifica
	int i=0, j=0, tmp=0;
	while (message[i]) {
		/*se la lettera corrente è maiuscola la porto temporaneamente in minuscolo
		sottraggo 'a' per avere la posizione nell'alfabeto,
		sommo la posizione corrente della chiave e sottraggo 26 se sono oltre la z*/
		if (isalpha(message[i])) {
			if (isupper(message[i])) {
				tmp=tolower(message[i])-'a';
				tmp+=c[j];
				if (tmp>25) {
					tmp-=26;
				}
				message[i]=toupper(tmp+'a');
			}
			else {
				tmp=message[i]-'a';
				tmp+=c[j];
				if (tmp>25) {
					tmp-=26;
				}
				message[i]=tmp+'a';
			}
			
			if (j<len-1)
				j++;
			else
				j=0;
		}
		i++;
	}
}

void decode(char chiave[], char message[]) {
	int len=strlen(chiave);
	int c[len];
	convertkey(c, chiave);

	//inizio la codifica
	int i=0, j=0, tmp=0;
	while (message[i]) {
		/*se la lettera corrente è maiuscola la porto temporaneamente in minuscolo
		sottraggo 'a' per avere la posizione nell'alfabeto,
		sottraggo la posizione corrente della chiave e sommo 26 se sono prima della a*/
		if (isalpha(message[i])) {
			if (isupper(message[i])) {
				tmp=tolower(message[i])-'a';
				tmp-=c[j];
				if (tmp<0) {
					tmp+=26;
				}
				message[i]=toupper(tmp+'a');
			}
			else {
				tmp=message[i]-'a';
				tmp-=c[j];
				if (tmp<0) {
					tmp+=26;
				}
				message[i]=tmp+'a';
			}
			
			if (j<len-1)
				j++;
			else
				j=0;
		}
		i++;
	}
}

int main () {
	char chiave[]= "CiB";
	char message[]= "DkBD";
	decode(chiave, message);
	int i=0;
	while (message[i]) {
		cout<<message[i];
		i++;
	}
	cout<<endl;
	return 0;
}
