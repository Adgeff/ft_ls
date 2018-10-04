/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optset3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 02:32:29 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/04 04:24:31 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	return (ft_aopt(env, opt));
}

int		ft_gopt(t_env *env, char opt)
{
	env->long_mask = env->long_mask & ~l_uid_mask;
	return (ft_lopt(env, opt));
}
