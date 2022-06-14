#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	close(STDOUT_FILENO);
	write(STDOUT_FILENO, "hello\n", 6);
	return (0);
}
