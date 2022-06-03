#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	printf("exit function test\n");
	if (argc == 1)
	{
		printf("no arguments\n");
		return (0);
	}
	exit(atoi(argv[1]));
}
