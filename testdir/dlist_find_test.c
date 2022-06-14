#include <stdio.h>
#include <stdlib.h>

#include "dlinkedlist.h"
#include "doubly_linked_list/dlinkedlist.h"
#include "libft.h"

#define SIZE (10)

typedef struct s_struct
{
	char	*line1;
	char	*line2;
}			t_struct;

static void	print_content(void *arg);
static void	*extract_content(void *arg);

int	main(void)
{
	t_struct	*var;
	t_dlist		*dlist;
	t_node		*node;

	dlist = dlist_init();
	for (int i = 0; i < SIZE; ++i)
	{
		var = malloc(sizeof(t_struct));
		*var = (t_struct){(ft_strdup(ft_itoa(i))), "abc"};
		push_back(dlist, var);
	}
	dlist_print_forward(dlist, print_content);
	node = dlist_find_content(dlist, "4", 1, extract_content);
	if (node != NULL)
		printf("find success\n");
	else
		printf("find fail\n");
}

void	print_content(void *arg)
{
	t_struct	*var = arg;

	printf("line1: %s\nline2: %s\n", var->line1, var->line2);
}

void	*extract_content(void *arg)
{
	t_struct	*var = arg;

	return (var->line1);
}
