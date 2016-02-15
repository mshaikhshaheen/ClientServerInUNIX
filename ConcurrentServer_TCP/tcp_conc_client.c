#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#define MAXLINE 4096
#define SERV_PORT 3001

int main(int argc,char **argv){
	int sockfd;
	struct sockaddr_in servaddr;
	char sendline[MAXLINE],recvline[MAXLINE];

	if(argc!=2){
		printf("Usage : TCPClient <IP of the server>");
		exit(0);	
	}
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0){
		printf("Problem creating socket");
		exit(0);	
	}
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	servaddr.sin_port = htons(SERV_PORT);
	if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
		printf("Not able to connect");
		exit(0);	
	}
	while(fgets(sendline,MAXLINE,stdin)!=NULL){
		write(sockfd,sendline,sizeof(sendline));
		read(sockfd,recvline,sizeof(recvline));	
		printf("String recieved is %s",recvline);	
	}
	close(sockfd);
}
