#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define TEXT_SZ 512
//THis is client

int main(void){
	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	char some_text[TEXT_SZ];
	char *choice = some_text;
	sockfd = socket(AF_INET,SOCK_STREAM,0);

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = 9734;
	len = sizeof(address);

	result = connect(sockfd, (struct sockaddr *)&address,len);
	if(result == -1){
		perror("oops: client2");
		exit(1);
	}
	do{
		read(sockfd,some_text,sizeof(some_text));
		some_text[strcspn(some_text, "\n")] = '\0';
		if(*choice == 'q' || *choice == 'Q'){
			close(sockfd);
			exit(0);
		}
		printf("\nRecieved data = %s\n",some_text);
		printf("SEND (q or Q to quit) : ");
		fgets(some_text,sizeof(some_text),stdin);
		write(sockfd, some_text,sizeof(some_text));
		some_text[strcspn(some_text, "\n")] = '\0';
	}while(*choice != 'q' && *choice != 'Q');
	close(sockfd);
	exit(0);
}
