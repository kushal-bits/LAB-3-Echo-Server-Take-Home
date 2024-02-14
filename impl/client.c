#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

typedef struct{
	int sd;
	char *addr;
	int port;
} Socket;

// Create a connection to the server
int create_connection(char* addr, int port) {
	MySocket *s = (MySocket *)malloc( sizeof(MySocket));
	s->sd = socket(AF_INET, SOCK_STREAM, 0);
	if(s->sd==-1){
		perror("Socket connection failed.");
	}	
	struct sockaddr_in servaddr, cli;
	bzero(servaddr, sizeof(servaddr);
	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
    	servaddr.sin_addr.s_addr = htonl(addr); 
    	servaddr.sin_port = htons(port); 
	if (connect(s->sd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("Connection failed\n");
		exit(0);
	} 
	else printf("Connected\n");
	socklen_t len = sizeof(cli);
        if (getsockname(s->sd, (struct sockaddr *)&cli, &len) == -1){
            perror("getsockname");
	}
        else{
            printf("%s:%d is connected to %s:%d\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port), addr, port);
	}
	return s->sd;
}

void send_data(int socket_id) {
	char buff[1024];
	bzero(buff, sizeof(buff));
	printf("Enter data: ");
	n = 0;
	while ((buff[n++] = getchar()) != '\n');
	write(socket_id, buff, sizeof(buff));
}

// Receive input from the server
void recv_data(int socket_id) {
	char buff[1024];
	bzero(buff, sizeof(buff));
	read(socket_id, buff, sizeof(buff));
	printf("From Server : %s", buff);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
	{
		printf("Use 2 cli arguments\n");
		return -1;
	}
    
	// extract the address and port from the command line arguments
	char *addr = argv[1];
	int port = argv[2];
	int socket_id = create_connection(addr, port);

	while (1)
    {
        send_data(socket_id);
        recv_data(socket_id);
    }
}
