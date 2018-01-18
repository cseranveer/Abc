#ifndef HEAD_H
#define HEAD_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<errno.h>
typedef struct
{
char op;
int op1;
int op2;
int pid;
}COMMAND;

typedef struct
{
int result;
}RESULT;

void allocateProcessor(int ex, COMMAND cmd);


#endif

