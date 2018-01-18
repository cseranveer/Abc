#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "../header/head.h"
COMMAND command;

int main(int argc, char *argv[])
{
	
	RESULT result;
	command = getCommand();
	result.res = command.op1 - command.op2;
	writeResult(result);
	
	return 0;
}
COMMAND getCommand()
{
	printf("\nSubtractor\n");
	int usrKey = 1256, mqIdent;
	// Get Queue Identifier.
	mqIdent = msgget(usrKey, IPC_CREAT | 0666);

	if(mqIdent == -1)
	{
		printf("\nCan't create message queue\n");
		exit(-1);
	}
	
	printf("Message Identifier is %d\n", mqIdent);
	
		// Send message in message queue
		if(msgrcv(mqIdent, &command, sizeof(command), 0, 0) == -1)
		{
			printf("\nMessage Rec Failed\n");
			
		}		
	
		printf("\nCType %d\n", command.msg_type);
		printf("\nCop %c\n", command.op);
		printf("\nCop1 %d\n", command.op1);
		printf("\nCop2 %d\n", command.op2);
		printf("\nCpid %d\n", command.pid);
	return command;
	
}
void writeResult(RESULT result)
{
	int usrKey = 1257, mqIdent;
	// Get Queue Identifier.
	mqIdent = msgget(usrKey, IPC_CREAT | 0666);

	if(mqIdent == -1)
	{
		printf("\nCan't create message queue\n");
		exit(-1);
	}

	int a;
		// Send message in message queue
		a = msgsnd(mqIdent, &result, sizeof(result), 0);
		if(a == -1)
		{
			printf("Sorry! Could'nt Send message");
			exit(-1);

		}
	
}