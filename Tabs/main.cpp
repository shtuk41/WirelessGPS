
#include <QApplication>
#include <QWidget>
#include <iostream>
#include <signal.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include "controller.h"
#include "tabs.h"
#include "comm.h"

using namespace std;


int 	iMsgID;
int	iCommSocket;

static void comm_terminate(int);

int main(int argc, char  *argv[])
{

	iMsgID = msgget(IPC_PRIVATE,O_RDWR|IPC_CREAT|IPC_EXCL|S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
	struct msqid_ds msqid_ds_struct;
	
	if (msgctl(iMsgID,IPC_STAT,&msqid_ds_struct) < 0)
	{
		cout << "MAIN  msgctl IPC_STAT failed with errno " << errno << endl;
		return 0;
	}
	
	msqid_ds_struct.msg_perm.mode = S_IWUSR|S_IRUSR;
	
	if (msgctl(iMsgID,IPC_SET,&msqid_ds_struct) < 0)
	{
		cout << "MAIN  msgctl IPC_SET failed" << endl;
		return 0;
	}
	
	

  pid_t pid  = fork();

  	if (pid  == 0)
	{
		//child
		//parent
		QApplication app(argc,argv);

	
		Controller	cController(iMsgID);
		Tabs		cTabs(&cController);

		cTabs.resize(400,500);
		cTabs.show();

		return app.exec();
		
	}
	else if (pid > 0)
	{
		

		if (signal(SIGCHLD,comm_terminate) == SIG_ERR)
		{
			cout << "signal error" << endl;
			exit(0);
		}

		communicate(iMsgID,iCommSocket);
	}
	else
	{
		cout << "Tabs fork failed" << endl;
		return 0;
	}

  
}

void comm_terminate(int signo)
{
	if (signo == SIGCHLD)
	{
		if (msgctl(iMsgID,IPC_RMID,0) < 0)
		{
			cout << "MAIN  msgctl IPC_RMID failed with errno " << errno << endl;
		}
		
		close(iCommSocket);
	
		wait(0);
		cout << "terminating comm" << endl;
		exit(0);
	}
}
