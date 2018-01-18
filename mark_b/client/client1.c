#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../header/head.h"
COMMAND cmd;
RESULT result;
void handler(int sig)
{

// Reading the result
	int fd;\
	char *sTocFifo =  "../fifos/sTocFifo";
	

	fd = open(sTocFifo, O_RDONLY);
	read(fd, &result,  sizeof(result));
	printf("\nResult of %d %c %d = %d.\n",cmd.op1, cmd.op, cmd.op2, result.result);

}

int main(int argc, char *argv[])
{	
	signal(2, handler);
	printf("\nCurrent Client: Client 1\n");
	cmd.op = '+';
	cmd.op1 = 1;
	cmd.op2 = 1;
	cmd.pid = getpid();
	int res, frk, fd, ex;
	char *cTosFifo = "../fifos/cTosFifo", fileDis[1], *sTocFifo =  "../fifos/sTocFifo";
	// Open FIFO for write only
    fd = open(cTosFifo, O_WRONLY);
    // Write cmd to pipe
	write(fd, &cmd, sizeof(cmd));
	pause();
	return 0;
}
