#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../header/head.h"

int main(int argc, char *argv[])
{	
	printf("Current Client: Client 3");
	COMMAND cmd;
	cmd.op = '*';
	cmd.op1 = 1;
	cmd.op2 = 1;
	cmd.pid = getpid();
	int res, frk, fd, ex;
	char *cTosFifo = "../fifos/cTosFifo", fileDis[1];
	res = mkfifo(cTosFifo, 0777);
	//printf("\nConnecting to server\n");
	

	if(res == 0)
	{
		printf("cTosFifo created successfully!");
	}

	// Open FIFO for write only
    fd = open(cTosFifo, O_RDWR);

 	 //printf("\n1\n");
		
	frk =  fork();

	switch(frk)
	{
		case 0:					
			//printf("\n3\n");
			sleep(1);	
			/*
			printf("\nCop is %c\n", cmd.op);
			printf("Cop1 is %d\n", cmd.op1);
			printf("Cop2 is %d\n", cmd.op2);
			printf("Cpid is %d\n", cmd.pid);
			*/
			ex = execl("../server/a.out", "", NULL);
			break;
		default:
			//printf("\n2\n");
			//sleep(1);
			write(fd, &cmd, sizeof(cmd));
			break;
	}

	RESULT result;

	char *sTocFifo =  "../fifos/sTocFifo";
	// Reading the result
	fd = open(sTocFifo, O_RDONLY);
	read(fd, &result,  sizeof(result));
	printf("\nResult of %d %c %d = %d.\n",cmd.op1, cmd.op, cmd.op2, result.result);







	return 0;
}