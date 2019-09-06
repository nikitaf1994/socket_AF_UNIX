#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SERVER_PATH   "./socket"  

char message[] = "Hello from client!\n";
char buf[sizeof(message)];

int main()
{
    	int sock;
    	struct sockaddr_un server;

    	sock = socket(AF_UNIX, SOCK_STREAM, 0);

    	if(sock < 0)
    	{
        	perror("socket");
        	exit(1);
    	}

    	server.sun_family = AF_UNIX;
	strcpy(server.sun_path, SERVER_PATH);

    	if(connect(sock, (struct sockaddr *)&server, sizeof(struct sockaddr_un)) < 0)
    	{
        	perror("connect");
        	exit(2);
    	}

    	send(sock, message, sizeof(message), 0);
    	recv(sock, buf, sizeof(message), 0);
    	printf("%s",buf);
    	close(sock);

    	return 0;
}
