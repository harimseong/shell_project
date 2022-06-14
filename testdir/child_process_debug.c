#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	char	**child_argv;
	size_t	argv_len;

	(void)argc;
	(void)envp;
	child_argv = malloc(2 * sizeof(char *));
	child_argv[0] = "cat";
	argv_len = 1;
	while (argv[argv_len] != NULL)
	{
		child_argv[argv_len] = argv[argv_len];
		++argv_len;
	}
	child_argv[argv_len] = NULL;
	pid = fork();
	if (pid == 0)
	{
		char	buf[10];
		read(0, buf, 10);
		return (0);
	}
	waitpid(0, NULL, 0);
	return (0);
}
