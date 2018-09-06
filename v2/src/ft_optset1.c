/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optset1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 17:38:04 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/06 21:53:55 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_bigaopt(t_env *env, char opt)
{
	(void)opt;
	env->select_f = &ft_nodot_select;
	return (0);
}

int		ft_bigropt(t_env *env, char opt)
{
	(void)opt;
	env->explore_f = &ft_recursive_explore;
	return (0);
}

int		ft_bigsopt(t_env *env, char opt)
{
	(void)opt;
	env->cmp_f = &ft_size_cmp;
	return (0);
}

int		ft_biguopt(t_env *env, char opt)
{
	(void)opt;
	env->gettime_f = &ft_getbirthtime;
	return (0);
}

int		ft_aopt(t_env *env, char opt)
{
	(void)opt;
	env->select_f = &ft_select_all;
	return (0);
}

int		ft_copt(t_env *env, char opt)
{
	(void)opt;
	env->gettime_f = &ft_getctime;
	return (0);
}

int		ft_dopt(t_env *env, char opt)
{
	(void)opt;
	env->readarg_f = &ft_nodirsreadarg;
	return (0);
}

int		ft_fopt(t_env *env, char opt)
{
	env->sort_f = &ft_rev_list;
	ft_aopt(env, opt);
	return (0);
}

int		ft_mopt(t_env *env, char opt)
{
	(void)opt;
	env->print_f = &ft_print_comma;
	return (0);
}

int		ft_ropt(t_env *env, char opt)
{
	(void)opt;
	env->sort_f = &ft_merge_sort_rev;
	return (0);
}

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
