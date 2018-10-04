/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 21:22:14 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 21:26:42 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_moveall_to(t_file **from, t_file **to)
{
	t_file	*tmp;

	while (*from)
	{
		tmp = (*from)->next;
		(*from)->next = *to;
		*to = *from;
		*from = tmp;
	}
}

void		ft_moveone_to(t_file **from, t_file **to)
{
	t_file	*tmp;

	tmp = (*from)->next;
	(*from)->next = *to;
	*to = *from;
	*from = tmp;
}

t_file		*ft_rev_list_loop(t_file *list)
{
	t_file	*ret;

	if (list->next)
		ret = ft_rev_list_loop(list->next);
	else
		return (list);
	list->next->next = list;
	return (ret);
}

void		ft_split_list(t_file **list, t_file **l1, t_file **l2)
{
	t_file	*tmp;

	*l1 = NULL;
	*l2 = NULL;
	while (*list)
	{
		tmp = (*list)->next;
		(*list)->next = *l1;
		*l1 = *list;
		*list = tmp;
		tmp = *l1;
		*l1 = *l2;
		*l2 = tmp;
	}
}
