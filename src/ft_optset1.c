/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optset1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 17:38:04 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/04 08:45:36 by geargenc         ###   ########.fr       */
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
	env->link_arg = env->link_arg | la_enable_mask;
	return (0);
}

int		ft_bigfopt(t_env *env, char opt)
{
	(void)opt;
	env->getsuffix_f = &ft_getsuffixbigf;
	env->normal_mask = env->normal_mask | n_suffix_mask;
	env->long_mask = env->long_mask | l_suffix_mask;
	env->link_arg = env->link_arg & la_disable_mask;
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
	env->link_arg = env->link_arg & la_unblock_mask;
	env->link_arg = env->link_arg | la_force_mask;
	return (0);
}
