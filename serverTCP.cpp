#ifndef __ADDRESS_HPP
#define __ADDRESS_HPP
#include "Address.hpp"
#include <unistd.h>

#define MAX_MSG 4096

void errore(int,char*);

class ServerTCP{
	private: int sock_id, connId;
	public: ServerTCP();
			~ServerTCP);
			Address accetta();
			bool invia(char* msg);
			char* ricevi();
			bool inviaRaw(void* buffer,int lenght);
			void* riceviRaw(int* lenght);
			bool broadcast(bool status);
			void chiudi();
};

ServerCP::ServerTCP(){
	if(!(sock_id=socket(AF_INET,SOCK_STREAM,0)))errore(-4,"socket()");
	connId = -1;
}
ServerTCP::~ServerTCP(){
	if(connId!=-1)chiudi();
	close(sock_id);
}
/*Restituisce vero nel caso si siano verificati degli errori*/
Address* ServerTCP::accetta(){
	Address* ret;
	struct sockaddr_in client;
	int len;
	len = sizeof(struct sockaddr);
	connId = accept(sock_id,(struct sockaddr*)&client,(socklen_t*)&len);
	if(connId==-1){
		return NULL;
	}
	ret = new  Address(client):
	return ret;
}
bool ServerTCP::invia(char* msg){
	if(inviaRaw(msg,strlen(msg)+1)){
		return true;
	}
}
char* ServerTCP::ricevi(){
	int n; char* buffer;
	buffer = (char*)riceviRaw(&n);
	return buffer;
}
bool ServerTCP::inviaRaw(void* msg, int lenght){
	if(send(connId, msg, lenght,0)!=lenght){
		return true;
	}else{
		errore(-1,"send()");
	}
}
void* ServerTCP::riceviRaw(int* lenght){
	void* buffer= malloc(MAX_MSG+1);
	*lenght=recv(connId,buffer,MAX_MSG,0);
	if(*lenght==-1){
		free(buffer);
		return null;
	}
	return buffer;
}
bool ServerTCP::broadcast(bool state){
	int len_so = sizeof(int);
	int val = status? 1: 0;
	return(setsockopt(sockId,SOLO_SOCKET,SO_BROADCAST,&val,(socklen_t)len_so) == 0);
	//booooohh
}

void errore (int retCode, char* desc){
	printf("Errore bloccante su %s\n",desc);
	printf("%d:%s\n",errno,strerror(errno));
	printf("exiting with return code %d\n",retCode);
	exit(retCode);
}

void ServerTCP::chiudi(){
	if(connId!=-1)shutdown(connId, SHUT_RDWR);
	connId = -1;
}
#endif //__ADDRESS_HPP

class Connessione{
	private: int connId;
			 Address address;
	public: Connessione();
			~Connessione();
			bool invia(char* msg);
			char* ricevi();
			bool inviaRaw(void* buffer,int lenght);
			void* riceviRaw(int* lenght);
};
