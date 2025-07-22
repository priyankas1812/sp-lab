/*Demonstrate wait avoiding the zombie state*/
#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

main()
{
	int pid,dip,cpid;
	pid=fork();
	if(pid==0)
	{
		printf("1st childs process id is %d\n",getpid());
		printf("first-child terminating from memory\n");
	}
	else
	{
		dip=fork();
		if(dip==0)
		{
			printf("2nd childs process id is %d\n",getpid());
			printf("second-child terminating\n");
		}
		else
		{
			cpid=wait(0);
			printf("Child with pid %d died\n",cpid);
			cpid=wait(0);
			printf("Child with pid %d died\n",cpid);
			printf("I am parent \n");
		}
	}
}
