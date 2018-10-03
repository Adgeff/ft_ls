/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_badargs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 21:05:28 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 21:05:44 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_badargs(t_env *env)
{
	t_file	*list;

	env->badargs = ft_rev_list(env, env->badargs, &ft_ascii_cmp);
	list = env->badargs;
	while (list)
	{
		ft_fillbuff(env, 2, env->prog_name);
		ft_fillbuff(env, 2, ": ");
		ft_fillbuff(env, 2, list->name);
		ft_fillbuff(env, 2, ": ");
		ft_fillbuff(env, 2, list->path);
		ft_fillbuff(env, 2, "\n");
		list = list->next;
	}
	ft_freelist(env->badargs);
	env->badargs = NULL;
}
