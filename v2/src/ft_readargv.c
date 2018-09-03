/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readargv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 12:13:10 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/03 15:57:11 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_opt				ft_opttab(int i)
{
	static t_opt	opttab[] = {
		{'A', &ft_bigaopt},
		{'R', &ft_bigropt},
		{'U', &ft_biguopt},
		{'a', &ft_aopt},
		{'c', &ft_copt},
		{'d', &ft_dopt},
		{'f', &ft_fopt},
		{'m', &ft_mopt},
		{'r', &ft_ropt},
		{'t', &ft_topt},
		{'u', &ft_uopt},
		{'\0', &ft_illegalopt}
	};

	return (opttab[i]);
}

int					ft_readopt(t_env *env, char opt)
{
	int				i;

	i = 0;
	while (ft_opttab(i).opt && ft_opttab(i).opt != opt)
		i++;
	return (ft_opttab(i).f(env, opt));
}

int					ft_readopts(t_env *env)
{
	int				i;
	int				j;

	i = 1;
	while (i < env->argc && env->argv[i][0] == '-' &&
		ft_strcmp(env->argv[i], "--"))
	{
		j = 1;
		while (env->argv[i][j])
		{
			if (ft_readopt(env, env->argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	if (i < env->argc && !ft_strcmp(env->argv[i], "--"))
		i++;
	env->argc = env->argc - i;
	env->argv = env->argv + i;
	return (0);
}

int					ft_readargs(t_env *env)
{
	int				i;

	i = 0;
	while (i < env->argc)
	{
		if (env->readarg_f(env, env->argv[i]))
			return (1);
		i++;
	}
	if (!env->argc && env->readarg_f(env, "."))
		return (1);
	return (0);
}

int					ft_readargv(t_env *env)
{
	if (ft_readopts(env) ||
		ft_readargs(env))
		return (1);
	return (0);
}
