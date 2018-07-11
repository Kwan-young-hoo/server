#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>

#define BUFF_SIZE 1024

void serv_function();
void server_daemon();
void socket_produce();
void accept_wait();
void error_handling(char *message);


	int server_socket;
	int client_socket;
	int client_addr_size;

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	
	char buff_rcv[BUFF_SIZE+5];
	char buff_snd[BUFF_SIZE+5];

		int main()
		{
		
			server_daemon();

			socket_produce();
		
		while(1)
			{
				accept_wait();
				sleep(10);
			}
		}


	
		void server_daemon()
			{
				pid_t pid;
			
				if ((pid = fork()) < 0)
				{
					exit(0);
					}
				else if (pid!=0)
				{
					exit(0);
					}

				chdir("/");
				setsid();
			}

		void socket_produce()
			{
		

				server_socket = socket(PF_INET, SOCK_STREAM, 0);
				if(-1 == server_socket){
				error_handling("socket() error");
				}

				memset(&server_addr, 0, sizeof(server_addr));
				server_addr.sin_family			= AF_INET;
				server_addr.sin_port			= htons(3300);
				server_addr.sin_addr.s_addr 	= htonl(INADDR_ANY);

				if(-1 == bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr))){
						error_handling("bind() error");
				}
			}

	
		void accept_wait()
			{
		
	
				if(-1 == listen(server_socket, 5)){
				error_handling("listen() error");
				}
	
				client_addr_size	= sizeof( client_addr);
				client_socket		= accept( server_socket, (struct sockaddr*)&client_addr, &client_addr_size);

				if (-1 == client_socket){
				error_handling("accept() error");
				}

				read (client_socket, buff_rcv, BUFF_SIZE);
				printf("receive: %s\n", buff_rcv);

				sprintf(buff_snd, "%d : %s", strlen(buff_rcv), buff_rcv);
				write(client_socket, buff_snd, strlen(buff_snd)+1);
				close(client_socket);
			}

		void error_handling(char* message)
		{
			fputs(message, stderr);
			fputs("\n", stderr);
			close(client_socket);
		}					



