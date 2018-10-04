/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optset1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 17:38:04 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/04 02:34:49 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_bigaopt(t_env *env, char opt)
{
	(void)opt;
	env->select_f = &ft_nodot_select;
	return (0);
}

int		ft_bigcopt(t_env *env, char opt)
{
	(void)opt;
	env->print_f = &ft_print_colvert;
	return (0);
}

int		ft_bigfopt(t_env *env, char opt)
{
	(void)opt;
	env->getsuffix_f = &ft_getsuffixbigf;
	env->normal_mask = env->normal_mask | n_suffix_mask;
	env->long_mask = env->long_mask | l_suffix_mask;
	if (!env->stat_f)
		env->stat_f = &lstat;
	return (0);
}

int		ft_biggopt(t_env *env, char opt)
{
	(void)opt;
	if (isatty(1) || getenv("CLICOLOR_FORCE"))
	{
		if (ft_config_colors(env))
			return (1);
		env->normal_mask = env->normal_mask | n_color_mask;
		env->long_mask = env->long_mask | l_color_mask;
	}
	return (0);
}

int		ft_bighopt(t_env *env, char opt)
{
	(void)opt;
	env->stat_f = &stat;
	return (0);
}
