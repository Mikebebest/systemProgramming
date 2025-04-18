#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define TEXT_SZ 512
//THis is server

int main(void){
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	char some_text[TEXT_SZ];
	char *choice = some_text;

	server_sockfd = socket(AF_INET,SOCK_STREAM,0);

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_address.sin_port = 9734;
	server_len = sizeof(server_address);
	bind(server_sockfd,(struct sockaddr *)&server_address,server_len);

	listen(server_sockfd,5);
	printf("\nTCPServer Waiting for client on port %d\n",server_address.sin_port);
	client_len = sizeof(client_address);
	client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);
	printf("I got a connection from (%s, %d)\n",inet_ntoa\
		(client_address.sin_addr),ntohs(client_address.sin_port));
	do{
		printf("SEND (q or Q to quit) : ");
		fgets(some_text,sizeof(some_text),stdin);	
		write(client_sockfd, some_text,sizeof(some_text));
		some_text[strcspn(some_text, "\n")] = '\0';
		if(*choice == 'q' || *choice == 'Q'){
			close(client_sockfd);
			exit(0);
		}
		read(client_sockfd, some_text,sizeof(some_text));
		some_text[strcspn(some_text, "\n")] = '\0';
		if(*choice == 'q' || *choice == 'Q'){
			close(client_sockfd);
			exit(0);
		}
		printf("\nRECIEVED DATA = %s\n",some_text);
	}while(*choice != 'q' && *choice != 'Q');
				
	close(client_sockfd);
}

