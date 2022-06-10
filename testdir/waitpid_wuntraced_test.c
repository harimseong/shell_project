#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

static int	child_process(void);

int	main(void)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		return (child_process());
	waitpid(pid, &status, 0);
	printf("\nchild status = %d\n", status);
	printf("child exit status = %d\n", WEXITSTATUS(status));
	return (0);
}

int	child_process(void)
{
	usleep(10000000);
	return (111);
}
