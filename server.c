#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include<string.h>
#include<stdio.h>

union semun{
	int val;
};

int main()
{
	int a=8,b=4;
	int key;
	key=ftok("key",97);
	int shmid=shmget(key,60,IPC_CREAT|0777);

	int sid;
	int keysem=ftok("keysem",69);
	sid=semget(keysem,2,IPC_CREAT|0777);
	
	union semun su;
	su.val=0;
	semctl(sid,0,SETVAL,su);
	su.val=1;
	semctl(sid,1,SETVAL,su);

	struct sembuf sb;
		
	sb.sem_num=0;
	sb.sem_op=-1;
	sb.sem_flg=0;
	
	semop(sid,&sb,1);
	
	sb.sem_num=1;
	sb.sem_op=0;
	sb.sem_flg=0;
	
	semop(sid,&sb,1);

	char * sh=NULL;
	

	

	sh=shmat(shmid,NULL,0);

	if(strcmp(sh,"+"))
	{
		sprintf(sh,"%d",a+b);
	}
	else if(strcmp(sh,"-"))
	{
		sprintf(sh,"%d",a-b);
	}
	else if(strcmp(sh,"*"))
	{
		sprintf(sh,"%d",a*b);
	}
	else if(strcmp(sh,"/"))
	{
		sprintf(sh,"%d",a/b);
	}

	printf("Recieved Req\n");
	printf("Return reply\n");

	sb.sem_num=0;
	sb.sem_op=1;
	sb.sem_flg=0;
	
	semop(sid,&sb,1);
	
	sb.sem_num=1;
	sb.sem_op=1;
	sb.sem_flg=0;
	
	semop(sid,&sb,1);
	
	return 0;
}

