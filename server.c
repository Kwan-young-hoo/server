#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
 
#define BUFF_SIZE 1024

void error_handling(char *message);
int client_socket;

	int main(void)
	{
		int server_socket;
		int client_addr_size;
 
		struct sockaddr_in server_addr;
		struct sockaddr_in client_addr;
 	
		char buff_rcv[BUFF_SIZE+5];
		char buff_snd[BUFF_SIZE+5];
		char message[] = "Hello World\n";
 
 
 
		server_socket = socket(PF_INET, SOCK_STREAM, 0);
		if(-1 == server_socket){
		error_handling("socket() error");
   		}
 
		memset(&server_addr, 0, sizeof(server_addr));
		server_addr.sin_family     = AF_INET;
		server_addr.sin_port       = htons(4000);
		server_addr.sin_addr.s_addr= htonl(INADDR_ANY);
 
		if(-1 == bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr))){
		error_handling("bind() error");
		}
 
		while(1){
		if(-1 == listen(server_socket, 5)){
		error_handling("server() error");	
		}
 
		client_addr_size  = sizeof( client_addr);
		client_socket     = accept( server_socket, (struct sockaddr*)&client_addr, &client_addr_size);
 
		if (-1 == client_socket){
		error_handling("accept() error");
		}
 
		read (client_socket, buff_rcv, BUFF_SIZE);
		printf("receive: %s\n", buff_rcv);
 
		sprintf(buff_snd, "%d : %s", strlen(buff_rcv), buff_rcv);
		write(client_socket, buff_snd, strlen(buff_snd)+1);          // +1: NULL까지 포함해서 전송
		close(client_socket);
  		}
	}	


	void error_handling(char* message)
	{
		fputs(message, stderr);
		fputs("\n", stderr);
		close(client_socket);
	}
