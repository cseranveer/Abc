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
int msg_type;
char op;
int op1;
int op2;
int pid;
}COMMAND;

typedef struct
{
int res;
}RESULT;

typedef struct
{
int msg_type;
char msg_payload[13];
}MESSAGE;

void allocateProcessor(int ex, COMMAND cmd);
void sendCommand();
COMMAND getCommand();
void writeResult(RESULT result);
void getResult();


#endif

