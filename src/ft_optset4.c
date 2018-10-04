/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optset4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 02:33:14 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/04 04:24:35 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_hopt(t_env *env, char opt)
{
	(void)opt;
	env->sizesize_f = &ft_sizeunitsize;
	env->sizeprint_f = &ft_sizeunitprint;
	return (0);
}

int		ft_iopt(t_env *env, char opt)
{
	(void)opt;
	env->normal_mask = env->normal_mask | n_inode_mask;
	env->long_mask = env->long_mask | l_inode_mask;
	return (0);
}

int		ft_kopt(t_env *env, char opt)
{
	(void)opt;
	env->blocksize = 1024;
	return (0);
}

int		ft_lopt(t_env *env, char opt)
{
	(void)opt;
	setlocale(LC_ALL, getenv("LANG"));
	if (!env->blocksize)
		ft_config_blocksize(env);
	env->now = time(NULL);
	env->print_f = &ft_print_long;
	env->total = 2;
	return (0);
}

int		ft_mopt(t_env *env, char opt)
{
	(void)opt;
	env->print_f = &ft_print_comma;
	return (0);
}
