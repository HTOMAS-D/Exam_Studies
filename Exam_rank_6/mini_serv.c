#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

typedef struct client {
    int id;
    char msg[424242];
} t_client;

t_client clients[1024];
char buffRead[424242], buffWrite[424242];
int max=0, next_id=0;
fd_set active_fds, Read_fds, Write_fds;

void errorExit(char *str){
    write(2, str, strlen(str)); 
    exit(1);
}

void sendMsg(int send_fd){
    for(int fd = 0; fd <= max; fd++){
        if(FD_ISSET(fd, &Write_fds) && fd != send_fd) 
            write(fd, buffWrite, strlen(buffWrite));
    }
}

int main(int ac, char **av){
    if(ac != 2)
        errorExit("Wrong number of arguments\n");
    int sockfd = max = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
        errorExit("Fatal error\n");
    FD_ZERO(&active_fds);
    FD_SET(sockfd, &active_fds);
    
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1]));

    if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
        errorExit("Fatal error\n");
	if (listen(sockfd, 10) != 0) 
        errorExit("Fatal error\n");

    while(1){
        Read_fds = Write_fds = active_fds;
        if(select(max + 1, &Read_fds, &Write_fds, NULL, NULL) < 0)
            continue;
        
        for(int fd = 0; fd <= max; fd++){
            if(FD_ISSET(fd, &Read_fds) && fd == sockfd){
                int ClientSocket = accept(sockfd, NULL, NULL);
				max = (ClientSocket > max) ? ClientSocket : max;
				clients[ClientSocket].id = next_id++;
				bzero(clients[ClientSocket].msg, strlen(clients[ClientSocket].msg));
				FD_SET(ClientSocket, &active_fds);
				sprintf(buffWrite, "server: client %d just arrived\n", clients[ClientSocket].id);
				sendMsg(ClientSocket);
				break;
            }
            if(FD_ISSET(fd, &Read_fds) && fd != sockfd){
                int read = recv(fd, buffRead, sizeof(buffRead), 0);
                if(read <= 0){
                    sprintf(buffWrite, "server: client %d just left\n", clients[fd].id);
					sendMsg(fd);
					FD_CLR(fd, &active_fds);
					close(fd);
					break;
                }
                else{
                    for(int i=0, j=strlen(clients[fd].msg); i<read; i++, j++)
					{
						clients[fd].msg[j] = buffRead[i];
						if(clients[fd].msg[j] == '\n')
						{
							clients[fd].msg[j] = '\0';
							sprintf(buffWrite, "client %d: %s\n", clients[fd].id, clients[fd].msg);
							sendMsg(fd);
							bzero(clients[fd].msg, strlen(clients[fd].msg));
							j=-1;
						}
					}
					break;
                }
            }
        }
    }
}