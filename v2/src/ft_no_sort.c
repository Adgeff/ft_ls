/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 14:13:22 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/03 12:06:29 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_file	*ft_rev_list_loop(t_file *list)
{
	t_file		*ret;

	if (list->next)
		ret = ft_rev_list_loop(list->next);
	else
		return (list);
	list->next->next = list;
	return (ret);
}

t_file			*ft_rev_list(t_env *env, t_file *list,
				int (*cmp)(t_env *, t_file *, t_file *))
{
	t_file		*ret;

	(void)env;
	(void)cmp;
	ret = ft_rev_list_loop(list);
	list->next = NULL;
	return (ret);
}
