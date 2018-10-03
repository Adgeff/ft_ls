/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 10:05:50 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/27 10:06:05 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_config_functions(t_env *env)
{
	env->readarg_f = &ft_defreadarg;
	env->sort_f = &ft_merge_sort;
	env->cmp_f = &ft_ascii_cmp;
	env->print_f = &ft_print_oebl;
	env->explore_f = &ft_explore;
	env->select_f = &ft_nohidden_select;
	env->gettime_f = &ft_getmtime;
	env->getsuffix_f = NULL;
	env->uidsize_f = &ft_uidnamesize;
	env->uidprint_f = &ft_uidnameprint;
	env->gidsize_f = &ft_gidnamesize;
	env->gidprint_f = &ft_gidnameprint;
	env->sizesize_f = &ft_sizebytesize;
	env->sizeprint_f = &ft_sizebyteprint;
	env->timeprint_f = &ft_shorttimeprint;
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
