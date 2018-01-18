#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../header/head.h"

int main(int argc, char *argv[])
{
	// From client
	COMMAND cmd;
	RESULT result;
	int fd; // TODO: name to be changed
	char *sTopFifo =  "../fifos/sTopFifo";
	// Read the data from client into cmd
	fd = open(sTopFifo, O_RDONLY);
	read(fd, &cmd,  sizeof(cmd));
	//Adding the Operands
	result.result = cmd.op1 + cmd.op1;
	//Towards Server now returning result
	int res,fdpTosFifo;
	char *pTosFifo =  "../fifos/pTosFifo";
	res = mkfifo(pTosFifo, 0777);
	if(res == 0)
	{
		printf("pTosFifo created successfully!");
	}
	// Open FIFO for write only
    fdpTosFifo = open(pTosFifo, O_RDWR);
    //Write API
    write(fdpTosFifo, &result, sizeof(result));
	return 0;
}