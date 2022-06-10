#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	int		pid;

	printf("parent pid = %d\n", (pid = getpid()));
	printf("process group id = %d\n", getpgid(pid));
	if (fork() != 0)
		return (0);
	printf("child pid = %d\n", pid = getpid());
	printf("child process group id = %d\n", getpgid(pid));
	return (0);
}
