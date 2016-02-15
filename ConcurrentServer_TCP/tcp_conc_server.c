#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <unistd.h>

#define MAXLINE 4096
#define SERV_PORT 3001
#define LISTENQ 8

int main(int argc,char *argv[] ){
	int listenfd,connfd,n;
	int childpid;
	socklen_t clilen;
	char buf[MAXLINE];
	struct sockaddr_in cliaddr,servaddr;
	
	if((listenfd = socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf("Problem creating socket");
		exit(1);
	}
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr =htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	
	bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	listen(listenfd,LISTENQ);
	
	for(;;){
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);
		if((childpid = fork())== 0)
		{
			close(listenfd);
					
			while((n = read(connfd,buf,MAXLINE))> 0){
				printf("%s",buf);
				write(connfd,buf,n);
			}
			close(connfd);
		}
	}
}
