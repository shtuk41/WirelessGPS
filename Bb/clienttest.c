#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff

#endif

#define BUFFER_LENGTH 128

int main(int argc, char *argv[])
{
    char *host = "192.168.7.2";
    char *transport = "tcp";
    
    char buffer[BUFFER_LENGTH + 1];
    
    int s,n;
    
    struct sockaddr_in sin;
    
    memset(&sin,0,sizeof(sin));
    
    sin.sin_family = AF_INET;
    
    sin.sin_port = 20000;
    
    struct hostent *phe;
    
    if ((phe = gethostbyname(host)))
    {
      memcpy(&sin.sin_addr,phe->h_addr,phe->h_length);
    }
    else if ((sin.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE)
    {
      printf("INADDR_NONE\n");
      exit(-1);
    }
    
    struct protoent *ppe;
    
    if ((ppe = getprotobyname(transport)) == 0)
    {
      printf("getrptobyname failed");
      exit(-1);
    }
    
    s = socket(PF_INET,SOCK_STREAM,0);
      
     if (s < 0)
     {
	printf("creating socket failed\n");
	exit(-1);
     }
    
    if(connect(s,(struct sockaddr *)&sin,sizeof(sin)) < 0)
    {
      printf("connect failed %i\n",s);
      exit(-1);
    }
    
    write(s,"$GPGGA\n",7);
      
    while ((n = read(s,buffer,BUFFER_LENGTH)) > 0)
    {
	int i = 0;
	for (;i < n;i++)
	{
		putchar(buffer[i]);
	}

	putchar('\n');
    }
    
    printf("\n");
    
    close(s);
    
    return 0;
    
}

