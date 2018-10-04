/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optset2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 02:31:45 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/04 04:24:25 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

int		ft_bigtopt(t_env *env, char opt)
{
	(void)opt;
	env->timeprint_f = &ft_longtimeprint;
	return (0);
}

int		ft_biguopt(t_env *env, char opt)
{
	(void)opt;
	env->gettime_f = &ft_getbirthtime;
	return (0);
}
