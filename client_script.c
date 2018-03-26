#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>

#define ip "14.139.155.214"
#define msg_max 200

int main(){
	printf("\n Enter ! to turn off the client\n ");
	int soket,uzunluk;
	soket=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in serverAdress;
	char msg1[msg_max];
	char msg2[msg_max];
	serverAdress.sin_family=AF_INET;
	serverAdress.sin_port=htons(9999);
	serverAdress.sin_addr.s_addr=inet_addr(ip);
	if(connect(soket,(struct sockaddr *)&serverAdress,sizeof(serverAdress))<0){
		printf("\n Connection unsuccessful.\n");
		exit(1); }
	else
		printf("\n Connection created.\n");

	while(1){
		
		printf("\n Write the text to sent : "); 
		fgets(msg1,msg_max,stdin);
		if(msg1[0]=='!') break;
		uzunluk=strlen(msg1)+1;
		send(soket,msg1,uzunluk,0);
		recv(soket,msg2,msg_max,0);
		printf("The text from Server : %s",msg2);
	}
	return 0;
}
