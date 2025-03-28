#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#include "comm.h"
#include "tabs_message.h"

#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff

#endif

#define BUFFER_LENGTH 128

using namespace std;

int communicate(int iMsgID, int &iCommSocket)
{
    char *host = (char*)"192.168.7.2";
    char *transport = (char*)"tcp";
    
    char buffer[BUFFER_LENGTH + 1];
    
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
      cout << "COMM INADDR_NONE\n" << endl;
      exit(-1);
    }
    
    struct protoent *ppe;
    
    if ((ppe = getprotobyname(transport)) == 0)
    {
      cout << "getrptobyname failed" << endl;
      exit(-1);
    }
    
    iCommSocket = socket(PF_INET,SOCK_STREAM,0);
      
     if (iCommSocket < 0)
     {
	cout << "creating socket failed\n" << endl;
	exit(-1);
     }
    
    if(connect(iCommSocket,(struct sockaddr *)&sin,sizeof(sin)) < 0)
    {
      cout << "connect failed " << iCommSocket << endl;
      exit(-1);
    }
    
  
   	 while (1)
	{	

		Tabs_Message	cRetMsg;
	
		memset(&cRetMsg,0,sizeof(Tabs_Message));

		int iMsgSize;
		
		if ((iMsgSize =msgrcv(iMsgID,&cRetMsg,TAB_MSG_LENGTH,TAB_MSG_TYPE_NMEA_SENTENCE_ID,MSG_NOERROR)) < 0)
		{
			if (errno == EIDRM)
			{
				cout << "Comm receieve EIDRM" << endl;
				return -1;
			}
			
			cout << "errno is " << errno << endl;
		}

		char *str;

		if (!strncmp(cRetMsg.mtext,"GGA",3))
			str = (char*)"$GPGGA\n";
		else if (!strncmp(cRetMsg.mtext,"GLL",3))
			str = (char*)"$GPGLL\n";
		else if (!strncmp(cRetMsg.mtext,"GSA",3))
			str = (char*)"$GPGSA\n";	
		else if (!strncmp(cRetMsg.mtext,"GSV",3))
			str = (char*)"$GPGSV\n";
		else if (!strncmp(cRetMsg.mtext,"RMC",3))
			str = (char*)"$GPRMC\n";
		else if (!strncmp(cRetMsg.mtext,"VTG",3))
			str = (char*)"$GPVTG\n";
		else
		{
			continue;	
		}	
		
		write(iCommSocket,str,strlen(str));

	    	Tabs_Message	cMsg;
	
		memset(&cMsg,0,sizeof(Tabs_Message));	
	
	
		cMsg.mtype = TAB_MSG_TYPE_NMEA_SENTENCE;

	
		int n = read(iCommSocket,buffer,BUFFER_LENGTH);
		
		int ii = 0;	
		
		for (; ii < n; ii++)
		  cMsg.mtext[ii] = buffer[ii];
		  
		  cMsg.mtext[ii++] = '\r';
		  cMsg.mtext[ii++] = '\n';
		  
	    
		if (msgsnd(iMsgID,&cMsg,TAB_MSG_LENGTH,IPC_NOWAIT) < 0)
		{
			if (errno == EAGAIN)
				cout << "Comm send message EAGAIN" << endl;
			else if (errno == EINTR)
			{
				cout << "Comm send message ENTR" << endl;	
				return -1;
			}
		}


	}
	    
    return 0;
    
}

