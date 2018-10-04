/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 02:32:51 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/04 03:23:03 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file		*ft_merge_sort_rev(t_env *env, t_file *list,
			long (*cmp)(t_env *, t_file *, t_file *))
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
			long (*cmp)(t_env *, t_file *, t_file *))
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

t_file		*ft_rev_list(t_env *env, t_file *list,
			long (*cmp)(t_env *, t_file *, t_file *))
{
	t_file	*ret;

	(void)env;
	(void)cmp;
	ret = ft_rev_list_loop(list);
	list->next = NULL;
	return (ret);
}
