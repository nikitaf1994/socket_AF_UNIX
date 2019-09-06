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
	char *msg = "Hello from client!\n";
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

    	cliaddr.sun_family = AF_UNIX;

	if(bind(sock, (const struct sockaddr *) &cliaddr, SUN_LEN(&cliaddr)) < 0 )
        {
                perror("bind");
                exit(2);
        }

	addr.sun_family = AF_UNIX;
        strcpy(addr.sun_path, SERVER_PATH);

	if(sendto(sock, (const char *)msg, strlen(msg), MSG_CONFIRM,(const struct sockaddr *) &addr, sizeof(addr))<0)
	{
		perror("sending datagram message");
	}

	bytes_read=recvfrom(sock, (char *)buf, 1024, MSG_WAITALL,(struct sockaddr *) &addr, &len);

	if(bytes_read<0)
        {
                perror("recv");
        }

	buf[bytes_read] = '\0';
	printf("%s",buf);
	close(sock);

    	return 0;
}
