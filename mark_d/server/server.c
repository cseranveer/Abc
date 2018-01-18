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
MESSAGE message;
COMMAND command;
RESULT result;

int main(int argc, char *argv[])
{
	printf("\nServer Running\n");

	int usrKey = 1255, mqIdent;
	// Get Queue Identifier.
	mqIdent = msgget(usrKey, IPC_CREAT | 0666);

	if(mqIdent == -1)
	{
		printf("\nCan't create message queue\n");
		return 0;
	}
	
	printf("Message Identifier is %d\n", mqIdent);
	int running = 1;
	while(running)
	{
		// Send message in message queue
		if(msgrcv(mqIdent, &command, sizeof(command), 0, 0) == -1)
		{
			printf("\nMessage Rec Failed\n");
			return 0;
		}
				
		//printf("\nSType %d\n", command.msg_type);
		//printf("\nSop %c\n", command.op);
		//printf("\nSop1 %d\n", command.op1);
		//printf("\nSop2 %d\n", command.op2);
		//printf("\nSpid %d\n", command.pid);
		allocateProcessor(0, command);
		
	}
	return 0;
}

void allocateProcessor(int ex, COMMAND cmd)
{
	char opType = cmd.op;
	switch( opType )
	{
		case '+':
			printf("\ncase add \n ");
			system("../processors/adder");
			sendCommand();
			getResult();
			break;
		case '-':
			printf("\ncase sub \n ");
			system("../processors/subtractor");
			sendCommand();
			getResult();
			break;
		case '*':
			printf("\ncase mul \n ");
			system("../processors/multiplier");
			sendCommand();
			getResult();
			break;
	}

}
void sendCommand()
{
	int usrKey = 1256, mqIdent;
	// Get Queue Identifier.
	mqIdent = msgget(usrKey, IPC_CREAT | 0666);
	if(mqIdent == -1)
	{
		printf("\nCan't create message queue\n");
		exit(-1);
	}
	
		int a;
		// Send message in message queue
		
			a = msgsnd(mqIdent, &command, 17, 0);
			if(a == -1)
			{
				printf("Sorry! Could'nt Send message");
				exit(-1);
			}
			
	
}


void getResult()
{
	int usrKey = 1257, mqIdent;
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
				
		printf("\nSResult is %d\n", result.res);
		writeResult(result);
		
	
}

void writeResult(RESULT result)
{
	int usrKey = 1258, mqIdent;
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


