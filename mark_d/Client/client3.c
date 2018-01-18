#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include "../header/head.h"

MESSAGE message;
COMMAND command;
RESULT result;
int main(int argc, char *argv[])
{	
	command.op  =  '+';
	command.op1 =  15;
	command.op2 =  15;
	command.pid =  getpid();


//	printf("\nCurrent Client: Client 1\n");
	
	int usrKey = 1255, mqIdent;
	// Get Queue Identifier.
	mqIdent = msgget(usrKey, IPC_CREAT | 0666);
	if(mqIdent == -1)
	{
		printf("\nCan't create message queue\n");
		return 0;
	}
	


		
		int a, i = 0;
		// Send message in message queue
		while(i < 100000)
		{
			a = msgsnd(mqIdent, &command, 17, 0);
			if(a == -1)
			{
				printf("Sorry! Could'nt Send message");
			}
			printf("Command by Client3:%d", i);
			getResult();
			i++;

		}
		


	
	return 0;
}

void getResult()
{
	int usrKey = 1258, mqIdent;
	// Get Queue Identifier.
	mqIdent = msgget(usrKey, IPC_CREAT | 0666);

	if(mqIdent == -1)
	{
		printf("\nCan't create message queue\n");
		exit(-1);
	}

	
		if(msgrcv(mqIdent, &result, sizeof(result), 0, 0) == -1)
		{
			printf("\nMessage Rec Failed\n");
			exit(-1);
		}
				
		printf("Result of %d + %d is: %d\n",command.op1, command.op2, result.res);
		
	
}