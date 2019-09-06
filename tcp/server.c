#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SERVER_PATH     "./socket"

int main()
{
	unlink(SERVER_PATH);//if last time cant close programm
	int sock, listener;
    	struct sockaddr_un server;
    	char buf[1024];
	char message[]="Hi from server\n";
    	int bytes_read;


    	listener = socket(AF_UNIX, SOCK_STREAM, 0);

    	if(listener < 0)
    	{
        	perror("socket");
        	exit(1);
    	}
	memset(&server, 0, sizeof(server));
    	server.sun_family = AF_UNIX;
	strcpy(server.sun_path, SERVER_PATH);

	if(bind(listener, (struct sockaddr *)&server, SUN_LEN(&server)) <0)
    	{
        	perror("bind");
        	exit(2);
    	}

    	listen(listener, 1);

    	while(1)
    	{
        	sock = accept(listener, NULL, NULL);

		if(sock < 0)
        	{
            		perror("accept");
            		exit(3);
        	}

      		while(1)
        	{
			send(sock, message, bytes_read, 0);
            		bytes_read = recv(sock, buf, 1024, 0);
            		if(bytes_read <= 0) exit(4);
			printf("%s",buf);
        	}

        	close(sock);
		unlink(SERVER_PATH);
	}

	return 0;
}
