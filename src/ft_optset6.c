/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optset6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 02:34:57 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/04 02:35:06 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_topt(t_env *env, char opt)
{
	(void)opt;
	env->cmp_f = &ft_time_cmp;
	return (0);
}

int		ft_uopt(t_env *env, char opt)
{
	(void)opt;
	env->gettime_f = &ft_getatime;
	return (0);
}

int		ft_xopt(t_env *env, char opt)
{
	(void)opt;
	env->print_f = &ft_print_colhor;
	return (0);
}

int		ft_1opt(t_env *env, char opt)
{
	(void)opt;
	env->print_f = &ft_print_oebl;
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
