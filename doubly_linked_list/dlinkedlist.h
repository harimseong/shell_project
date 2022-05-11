/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlinkedlist.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:19:18 by hseong            #+#    #+#             */
/*   Updated: 2022/05/11 15:10:07 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLINKEDLIST_H
# define DLINKEDLIST_H

# include "minishell_type.h"

typedef t_token	t_item;

typedef struct s_node
{
	t_item			*item;
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;

typedef struct s_dlist
{
	t_node		*head;
	t_node		*tail;
	t_node		*cur;
	size_t		size;
	size_t		idx;
	int			flag;
}				t_dlist;

t_dlist	*dlist_init(void);

// CREATE AND DELETE
int		push_front(t_dlist *list, t_item *item);
int		push_back(t_dlist *list, t_item *item);
void	pop_front(t_dlist *list, void (*delete_item)(t_item *));
void	pop_back(t_dlist *list, void (*delete_item)(t_item *));
void	delete_dlist(t_dlist *list, void (*delete_item)(t_item *));
void	empty_dlist(t_dlist *list, void (*delete_item)(t_item *));

// UPDATE cur
void	move_front(t_dlist *list);
void	move_back(t_dlist *list);
void	set_cur(t_dlist *list, t_item *item);

// READ
void	peek_front(t_dlist *list, void (*print_item)(t_item *));
void	peek_back(t_dlist *list, void (*print_item)(t_item *));
t_item	*get_front(t_dlist *list);
t_item	*get_back(t_dlist *list);
void	print_dlist_forward(t_dlist *list, void (*print_item)(t_item *));
void	print_dlist_backward(t_dlist *list, void (*print_item)(t_item *));

// utils
void	ft_putnbr_space(int num);
void	mergesort_dlist(t_dlist *list);
t_dlist	*duplicate_dlist(t_dlist *list);

#endif
