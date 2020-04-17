#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include<string.h>
#include<stdio.h>

union semun{
	int val;
};

int main(int argc,char * argv[])
{
	int key;
	key=ftok("key",97);
	int shmid=shmget(key,0,0);

	int sid;
	int keysem=ftok("keysem",69);
	sid=semget(keysem,0,0);

	struct sembuf sb;
	
	sb.sem_num=0;
	sb.sem_op=0;
	sb.sem_flg=0;
	
	semop(sid,&sb,1);

	sb.sem_num=1;
	sb.sem_op=-1;
	sb.sem_flg=0;
	
	semop(sid,&sb,1);

	char * sh=NULL;
	sh=shmat(shmid,NULL,0);
	sprintf(sh,"%s",argv[1]);

	
	sb.sem_num=0;
	sb.sem_op=1;
	sb.sem_flg=0;
	
	semop(sid,&sb,1);

	sb.sem_num=1;
	sb.sem_op=0;
	sb.sem_flg=0;
	
	semop(sid,&sb,1);


	sb.sem_num=0;
	sb.sem_op=-1;
	sb.sem_flg=0;
	
	semop(sid,&sb,1);

	sb.sem_num=1;
	sb.sem_op=-1;
	sb.sem_flg=0;
	
	semop(sid,&sb,1);


	sh=shmat(shmid,NULL,0);

	char str[3];
	sscanf(sh,"%s",str);
	printf("%s\n",str);

	
	sb.sem_num=0;
	sb.sem_op=0;
	sb.sem_flg=0;
	
	semop(sid,&sb,1);

	sb.sem_num=1;
	sb.sem_op=1;
	sb.sem_flg=0;
	
	semop(sid,&sb,1);

	return 0;
}
	
