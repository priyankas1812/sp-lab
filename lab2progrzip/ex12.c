/* This program eliminates zombies in a process */
/* Observe the output second child ppid is 1, that means parent is init process
	 Read the manual pages of waitpid system call.

*/

#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main(){ 
	pid_t pid ;
	pid=fork();
	if ( pid < 0 )
		fprintf(stderr,"Fork error");
                   printf("%d",pid);
	else if ( pid == 0 ){
		pid=fork();
		if ( pid < 0 )
			fprintf(stderr,"fork error");
		else if ( pid > 0 )
			printf("%d",pid);
			exit(0);

		/* We are the second child; our parent becomes init as soon as our real parent call exit() in the statement above. Here's where we had continue executing, knowing that when we are done, init will reap our status
		*/

		sleep(2);
		printf("second child, parent pid = %d\n",getppid());
		exit(0);
	}

	if ( waitpid(pid,NULL,0) != pid)
		fprintf(stderr,"waitpid error");


	/* We are the parent ( the original process); we continue executing. knowing that we're not the parent of the second child. */
	exit(0);
}
