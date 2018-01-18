#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../header/head.h"

int main(int argc, char *argv[])
{
	
	COMMAND cmd;
	RESULT result;
	int fd,
		frk, 
		fdsTopFifo, 
		ex, res, 
		res1,fdsTocFifo
		,ki;

	char *cTosFifo = "../fifos/cTosFifo",
		 *sTopFifo =  "../fifos/sTopFifo",
		 *pTosFifo =  "../fifos/pTosFifo",
		 *sTocFifo =  "../fifos/sTocFifo";

	res = mkfifo(cTosFifo, 0777);
	if(res == 0)
	{
		printf("cTosFifo created successfully!");
	}
while(1)
{

	// Read the data from client into cmd
	
	fd = open(cTosFifo, O_RDONLY);
	read(fd, &cmd,  sizeof(cmd));

	if(fd < 0)
	{
		printf("\nCan not open cTosFifo FIFO\n");
	}
	else
	{
		unlink(cTosFifo);	
	}

	//Towards Processors
	res = mkfifo(sTopFifo, 0777);
	if(res == 0)
	{
		printf("sTopFifo created successfully!");
	}
	
	// Open FIFO for write only
    fdsTopFifo = open(sTopFifo, O_WRONLY);
   

    frk =  fork();
	switch(frk)
	{
		case 0:				
			printf("\ncheck1\n");
			allocateProcessor(ex, cmd);
			break;
		default:
			printf("\ncheck2\n");

			write(fdsTopFifo, &cmd, sizeof(cmd));
			
			//Towards client now returning result
			// Reading the result
			fd = open(pTosFifo, O_RDONLY);
			read(fd, &result,  sizeof(result));
			
			res1 = mkfifo(sTocFifo, 0777);

			if(res1 == 0)
			{
				printf("sTocFifo created successfully!");
			}

			// Open FIFO for write only
		    fdsTocFifo = open(sTocFifo, O_RDWR);
		    // Write to the result pipe
			
			write(fdsTocFifo, &result, sizeof(result));
		   	ki = kill(cmd.pid, 2);
		
		   	break;

	}
		 
}

	
	
   


	return 0;
}

void allocateProcessor(int ex, COMMAND cmd)
{
	char opType = cmd.op;
	switch( opType )
	{
		case '+':
			//printf("\n+ case add\n ");
			ex = execl("../processors/adder", "", NULL);
			break;
		case '-':
			//printf("\ncase subtract \n ");
			ex = execl("../processors/subtractor", "", NULL);
			break;
		case '*':
			//printf("\n+ case multiply\n ");
			ex = execl("../processors/multiplier", "", NULL);
			break;
	}

}

