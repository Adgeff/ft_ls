/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 02:32:51 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/03 12:06:05 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

t_file		*ft_merge_sort_rev(t_env *env, t_file *list,
			int (*cmp)(t_env *, t_file *, t_file *))
{
	t_file	*l1;
	t_file	*l2;

	if (!list->next)
		return (list);
	ft_split_list(&list, &l1, &l2);
	if (l1 && l1->next)
		l1 = ft_merge_sort(env, l1, cmp);
	if (l2 && l2->next)
		l2 = ft_merge_sort(env, l2, cmp);
	while (l1 && l2)
	{
		if (cmp(env, l1, l2) > 0)
			ft_moveone_to(&l2, &list);
		else
			ft_moveone_to(&l1, &list);
	}
	if (l1 || l2)
		l1 ? ft_moveall_to(&l1, &list) : ft_moveall_to(&l2, &list);
	return (list);
}

t_file		*ft_merge_sort(t_env *env, t_file *list,
			int (*cmp)(t_env *, t_file *, t_file *))
{
	t_file	*l1;
	t_file	*l2;

	if (!list->next)
		return (list);
	ft_split_list(&list, &l1, &l2);
	if (l1 && l1->next)
		l1 = ft_merge_sort_rev(env, l1, cmp);
	if (l2 && l2->next)
		l2 = ft_merge_sort_rev(env, l2, cmp);
	while (l1 && l2)
	{
		if (cmp(env, l1, l2) < 0)
			ft_moveone_to(&l2, &list);
		else
			ft_moveone_to(&l1, &list);
	}
	if (l1 || l2)
		l1 ? ft_moveall_to(&l1, &list) : ft_moveall_to(&l2, &list);
	return (list);
}
