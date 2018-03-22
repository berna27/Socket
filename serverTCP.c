#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_CONN 50
#define MAX_MSG 4096

int main(int argc,char* argv[]){
	
	if(argc!=3){printf("USAGE: %s PORT MSG \n",argv[0]);return -1;}
	
	char buffer[MAX_MSG+1];
	int sock_id,conn_id,ret,i;
	int dim=sizeof(struct sockaddr_in);
	int len = strlen(argv[2])+1;
	
	sock_id=socket(AF_INET,SOCK_STREAM,0);
	
	struct sockaddr_in myself;
	
	myself.sin_family=AF_INET;
	inet_aton("127.0.0.1",&myself.sin_addr);
	myself.sin_port=htons(atoi(argv[1]));
	for(int i=0;i<8;i++){
		myself.sin_zero[i]=0;
	}
	
	ret=bind(sock_id,(struct sockaddr*)&myself,(socklen_t)dim);
	if(ret!=0){printf("ERRORE: bind()") return -2;}
	
	if(listen(sock_id, MAX_CONN)!=0){printf("ERRORE: listen()");return -3;}
	
	conn_id=accept(sock_id, (struct sockaddr*)&myself, (socklen_t*)&dim);
	
	if (conn_id<=0){printf("ERRORE: accept()");return -4;}
	
	ret=recv(conn_id,buffer,MAX_MSG,0);
	if(ret<=0){printf("ERRORE:recv()");return -5;}
	buffer[ret]='\0';
	
	printf("Messggio: %s\n",buffer);
	
	if(send(conn_id,argv[2],len,0)!=len){
		printf("ERRORE :send()");
		return -6;
	}
	
	shutdown(conn_id,SHUT_RDWR);
	close(sock_id);
	return 0;
	
}