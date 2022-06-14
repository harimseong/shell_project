#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void	child_routine(int fd);

int	main(void)
{
	int	pipe_fd[2];
	int	stdout_dup;
	char	buf[100];

	(void)pipe_fd;
//	pipe(pipe_fd);
	stdout_dup = dup(STDOUT_FILENO);
	pipe_fd[1] = dup(STDOUT_FILENO);
	printf("log\n");
	system("lsof -p $(ps > psout2 && grep < psout2 a.out | cut -d ' ' -f 1 | head -n 1)");
	system("lsof -p $(ps > psout2 && grep < psout2 a.out | cut -d ' ' -f 1 | head -n 2)");
	printf("\n\n");
	write(stdout_dup, "abc\n", 4);
	write(pipe_fd[1], "pipe write\n", 11);
	close(pipe_fd[1]);
	printf("log\n");
	system("lsof -p $(ps > psout2 && grep < psout2 a.out | cut -d ' ' -f 1 | head -n 1)");
	system("lsof -p $(ps > psout2 && grep < psout2 a.out | cut -d ' ' -f 1 | head -n 2)");
	printf("\n\n");
	if (fork() == 0)
	{
		child_routine(pipe_fd[0]);
		return (0);
	}
	printf("log\n");
	system("lsof -p $(ps > psout2 && grep < psout2 a.out | cut -d ' ' -f 1 | head -n 1)");
	system("lsof -p $(ps > psout2 && grep < psout2 a.out | cut -d ' ' -f 1 | head -n 2)");
	printf("\n\n");
	read(0, buf, 1);
	return (0);
}

void	child_routine(int fd)
{
	printf("log\n");
	system("lsof -p $(ps > psout2 && grep < psout2 a.out | cut -d ' ' -f 1 | head -n 1)");
	system("lsof -p $(ps > psout2 && grep < psout2 a.out | cut -d ' ' -f 1 | head -n 2)");
	printf("\n\n");
	char	buf[100];
	write(1, "type anything to continue\n", 26);
	read(fd, buf, 1000);
	write(1, buf, strlen(buf));
	printf("log\n");
	system("lsof -p $(ps > psout2 && grep < psout2 a.out | cut -d ' ' -f 1 | head -n 1)");
	system("lsof -p $(ps > psout2 && grep < psout2 a.out | cut -d ' ' -f 1 | head -n 2)");
	printf("\n\n");
	read(0, buf, 1);
}
