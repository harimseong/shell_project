#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int	main(int argc, char *argv[], char *envp[])
{
	char	*str;

	(void)argc;
	(void)argv;
	str = calloc(1, 10);
	str[0] = '.';
	str[1] = '.';
	str[2] = 0;
	execve(str, &str, envp);
	perror(NULL);
	return (0);
}
