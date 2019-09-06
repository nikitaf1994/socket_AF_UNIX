#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define SERVER_PATH     "./socket"

int main()
{
	unlink(SERVER_PATH);//if failed last time programm didnot closed
	char *msg = "Hi from server!\n";
    	int sock;
    	struct sockaddr_un addr, cliaddr; 
    	char buf[1024];
    	int bytes_read;
	int len;

    	sock = socket(AF_UNIX, SOCK_DGRAM, 0);

    	if(sock < 0)
    	{
        	perror("socket");
        	exit(1);
    	}

	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, SERVER_PATH);

    	if(bind(sock, (const struct sockaddr *) &addr, SUN_LEN(&addr)) < 0 )
    	{
        	perror("bind");
        	exit(2);
    	}

	bytes_read=recvfrom(sock, (char *)buf, 1024, MSG_WAITALL, (struct sockaddr *) &cliaddr, &len);
	buf[bytes_read] = '\0';
	printf("%s",buf);

	if(sendto(sock, (const char *)msg, strlen(msg), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, sizeof(cliaddr))<0)
	{
		perror("sending datagram message");
	}

    	return 0;
}
