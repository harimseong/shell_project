#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(void)
{
	int		pipe_fd[2];
	int		pid;
	char	buf[100];

	if (pipe(pipe_fd) < 0)
	{
		perror("pipe error");
		return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		int	write_bytes;
		
		write_bytes = write(pipe_fd[1], "hello\n", 6);
		read(0, buf, 100);
		return (write_bytes < 0);
	}
	wait(NULL);
	read(pipe_fd[0], buf, 100);
	printf("%s", buf);
	return (0);
}
