#include <unistd.h>
#include <string.h>

int	main(void)
{
	char	buf[100];
	int		pipe_fd[2];

	pipe(pipe_fd);
	write(pipe_fd[1], "hello pipe!\n", 12);
	close(pipe_fd[1]);
	usleep(1000000);
	read(pipe_fd[0], buf, 100);
	write (STDOUT_FILENO, buf, strlen(buf));
	return (0);
}
