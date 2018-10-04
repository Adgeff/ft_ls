/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readargv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 12:13:10 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/04 08:44:17 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_opt				ft_opttab(int i)
{
	static t_opt	opttab[] = {
		{'A', &ft_bigaopt}, {'C', &ft_bigcopt},
		{'F', &ft_bigfopt}, {'G', &ft_biggopt},
		{'H', &ft_bighopt}, {'P', &ft_bigpopt},
		{'R', &ft_bigropt}, {'S', &ft_bigsopt},
		{'T', &ft_bigtopt}, {'U', &ft_biguopt},
		{'a', &ft_aopt}, {'c', &ft_copt},
		{'d', &ft_dopt}, {'f', &ft_fopt},
		{'g', &ft_gopt}, {'h', &ft_hopt},
		{'i', &ft_iopt}, {'k', &ft_kopt},
		{'l', &ft_lopt}, {'m', &ft_mopt},
		{'n', &ft_nopt}, {'o', &ft_oopt},
		{'p', &ft_popt}, {'r', &ft_ropt},
		{'s', &ft_sopt}, {'t', &ft_topt},
		{'u', &ft_uopt}, {'x', &ft_xopt},
		{'1', &ft_1opt}, {'\0', &ft_illegalopt}
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
		ft_strcmp(env->argv[i], "--") && env->argv[i][1])
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

	if (env->link_arg & la_block_mask)
		env->link_arg = la_none_mask;
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
