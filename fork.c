#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
	pid_t pid;
	printf("Program start...\n");

	while(1) {
		pid = fork();
		if(pid == 0)
			printf("I'm child.\n");
		else
			printf("I'm parent\n");
		sleep(2);
	}
}
