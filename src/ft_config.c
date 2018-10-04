/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 10:05:50 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/04 02:05:20 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_config_functions(t_env *env)
{
	env->cmp_f = &ft_ascii_cmp;
	env->explore_f = &ft_explore;
	env->getsuffix_f = NULL;
	env->gettime_f = &ft_getmtime;
	env->gidprint_f = &ft_gidnameprint;
	env->gidsize_f = &ft_gidnamesize;
	env->print_f = &ft_print_oebl;
	env->readarg_f = &ft_defreadarg;
	env->select_f = &ft_nohidden_select;
	env->sizeprint_f = &ft_sizebyteprint;
	env->sizesize_f = &ft_sizebytesize;
	env->sort_f = &ft_merge_sort;
	env->stat_f = NULL;
	env->timeprint_f = &ft_shorttimeprint;
	env->uidprint_f = &ft_uidnameprint;
	env->uidsize_f = &ft_uidnamesize;
}

void				ft_config_term(t_env *env)
{
	struct winsize	win;

	ioctl(1, TIOCGWINSZ, &win);
	env->ws_col = win.ws_col;
	env->print_f = &ft_print_colvert;
}

void				ft_config(t_env *env)
{
	ft_config_functions(env);
	env->ws_col = 80;
	env->size = 0;
	env->total = 0;
	env->normal_mask = n_def_mask;
	env->long_mask = l_def_mask;
	env->blocksize = 0;
	env->colortab = NULL;
	env->badargs = NULL;
	env->fileargs = NULL;
	env->dirargs = NULL;
	if (isatty(1))
		ft_config_term(env);
}
