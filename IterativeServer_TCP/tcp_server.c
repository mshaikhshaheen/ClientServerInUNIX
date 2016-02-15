#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#define MAXLINE 4096
#define SERV_PORT 3000
#define LISTENQ 8

int main(int argc,char **argv){
	printf("SERVER WELCOMES YOU!");		
	int listenfd,connfd,n;
	socklen_t clilen;
	char buf[MAXLINE];
	struct sockaddr_in cliaddr,servaddr;
	
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr =htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	
	bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	listen(listenfd,LISTENQ);
	
	for(;;){
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);
		while((n = read(connfd,buf,MAXLINE))> 0)
			write(connfd,buf,n);
	}
		close(connfd);
	close(listenfd);
}
