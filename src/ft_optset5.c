/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optset5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 02:34:24 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/04 09:32:36 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_nopt(t_env *env, char opt)
{
	env->uidsize_f = &ft_uididsize;
	env->uidprint_f = &ft_uididprint;
	env->gidsize_f = &ft_gididsize;
	env->gidprint_f = &ft_gididprint;
	return (ft_lopt(env, opt));
}

int		ft_oopt(t_env *env, char opt)
{
	env->long_mask = env->long_mask & ~l_gid_mask;
	return (ft_lopt(env, opt));
}

int		ft_popt(t_env *env, char opt)
{
	(void)opt;
	env->getsuffix_f = &ft_getsuffixp;
	env->normal_mask = env->normal_mask | n_suffix_mask;
	env->long_mask = env->long_mask | l_suffix_mask;
	env->link_arg = env->link_arg & la_disable_mask;
	return (0);
}

int		ft_ropt(t_env *env, char opt)
{
	(void)opt;
	env->sort_f = &ft_merge_sort_rev;
	return (0);
}

int		ft_sopt(t_env *env, char opt)
{
	(void)opt;
	if (!env->blocksize)
		ft_config_blocksize(env);
	env->total = env->total | t_block_mask;
	env->normal_mask = env->normal_mask | n_blocks_mask;
	env->long_mask = env->long_mask | l_blocks_mask;
	return (0);
}
