#include<stdio.h>
#include<semaphore.h>
#include <sys/sem.h>
#include<time.h>
#include <errno.h>
struct sembuf sbuf;
union semun 
{
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO*/

};
union semun sval;

int main()
{
	int i = 0, k_key;
	k_key = getKernelKey();

	sval.val = 1;


	// Set value
	   if (semctl(k_key, 0, SETVAL, sval) < 0)
	    {
	        perror("Could not set value of semaphore");
		}

	
	for(;i<10;i++)
	{
		if(get_semaphore() == 0)
		{
			sleep(1);
			printf("%d\n",getpid());
			sleep(1);
			release_semaphore();
		}
	}
	
	return 0;
}
int getKernelKey()
{
	int k_key = semget (1112, 1, IPC_CREAT);
	if (k_key < 0) 
	{
         perror("Could not create sem");
	}
	return k_key;	
}


int  get_semaphore()
{
	
	sbuf.sem_num = 0;
	sbuf.sem_op = -1;
	sbuf.sem_flg = SEM_UNDO;
	// Handle Flag here
	return 0;
}

int release_semaphore()
{
	sbuf.sem_num = 0;
	sbuf.sem_op =  1;
	sbuf.sem_flg = SEM_UNDO;
	// Handle Flag here
	return 0;
}