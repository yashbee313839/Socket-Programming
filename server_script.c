#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include <unistd.h>

#define uzunluk 100
int main(){
	int socket1,soc_1,c_uzunlugu,n,sayac=1;
	struct sockaddr_in serverAdress;
	struct sockaddr_in clientAdress;
	char mesaj[uzunluk];

	socket1=socket(AF_INET,SOCK_STREAM,0);
	
	serverAdress.sin_family=AF_INET;
	serverAdress.sin_port=htons(9999);
	serverAdress.sin_addr.s_addr=INADDR_ANY;

	if(bind(socket1,(struct sockaddr *)&serverAdress,sizeof(serverAdress))<0){
		printf("Not Created Socket \n");
		exit(1);
	}
	else
		printf("Created Socket.\n");

	listen(socket1,10);
	printf("Listening\n");

	while (1){
		c_uzunlugu=sizeof(clientAdress);
		soc_1=accept(socket1,(struct sockaddr *)&clientAdress,&c_uzunlugu);

		if(soc_1>0){
				printf("%d.Created Connection.\n",sayac);
				sayac++; }	
				 
		else
				printf("Not Created Connection!!!!\n");

		if(!fork()){
			while(1){
				recv(soc_1,mesaj,uzunluk,0);	
				n=strlen(mesaj)+1;
				printf("\n the text from client: %s",mesaj);
				printf("write text to client : %s",mesaj);
				send(soc_1,mesaj,n,0);
				}	
			exit(1);
			}
		else{
		close(soc_1);
		}
	}
	return 0;
}
