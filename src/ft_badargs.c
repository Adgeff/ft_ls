/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_badargs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 21:05:28 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/04 07:41:31 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_badargs(t_env *env)
{
	t_file	*list;

	env->badargs = ft_merge_sort(env, env->badargs, &ft_ascii_cmp);
	list = env->badargs;
	while (list)
	{
		ft_putstr_fd(2, env->prog_name);
		ft_putstr_fd(2, ": ");
		ft_putstr_fd(2, list->name);
		ft_putstr_fd(2, ": ");
		ft_putstr_fd(2, list->path);
		ft_putstr_fd(2, "\n");
		list = list->next;
	}
	ft_freelist(env->badargs);
	env->badargs = NULL;
}
