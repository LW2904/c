#include <stdio.h>
#include <unistd.h>		// getopt()
#include <stdlib.h>		// strol()
#include <signal.h>

extern char *optarg;

int main(int argc, char **argv)
{
	int c;
	pid_t pid;

	while ((c = getopt(argc, argv, "p:")) != -1) {
		switch (c) {
		case 'p':
			pid = (pid_t)strtol(optarg, NULL, 10);
		}
	}

	if (kill(pid, 0) < 0) {
		printf("process with id %d does not exist\n", pid);
	} else {
		printf("process with id %d found\n", pid);
	}

	return 0;
}
