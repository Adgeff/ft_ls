/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optset1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 17:38:04 by geargenc          #+#    #+#             */
/*   Updated: 2018/06/08 14:47:29 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// int		ft_aopt(t_env *env, char opt)
// {
// 	(void)opt;
// 	return (0);
// }

int		ft_dopt(t_env *env, char opt)
{
	(void)opt;
	env->readarg_f = &ft_nodirsreadarg;
	return (0);
}

int		ft_fopt(t_env *env, char opt)
{
	(void)opt;
	env->sort_f = &ft_rev_list;
	return (0);
}

int		ft_ropt(t_env *env, char opt)
{
	(void)opt;
	env->sort_f = &ft_merge_sort_rev;
	return (0);
}

int		ft_illegalopt(t_env *env, char opt)
{
	int	i;

	ft_fillbuff(env, 2, env->prog_name);
	ft_fillbuff(env, 2, ": illegal option -- ");
	ft_fillbuff_c(env, 2, opt);
	ft_fillbuff(env, 2, "\nusage: ");
	ft_fillbuff(env, 2, env->prog_name);
	ft_fillbuff(env, 2, " [-");
	i = 0;
	while (ft_opttab(i).opt)
	{
		ft_fillbuff_c(env, 2, ft_opttab(i).opt);
		i++;
	}
	ft_fillbuff(env, 2, "] [file ...]\n");
	ft_writebuff(env);
	return (1);
}
