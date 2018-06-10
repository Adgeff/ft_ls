/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 14:13:22 by geargenc          #+#    #+#             */
/*   Updated: 2018/06/08 14:47:31 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

t_file		*ft_rev_list(t_file *list, int (*f)(t_file *, t_file *))
{
	t_file	*ret;

	(void)f;
	ret = ft_rev_list_loop(list);
	list->next = NULL;
	return (ret);
}
