/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optset1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 17:38:04 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/20 14:45:54 by geargenc         ###   ########.fr       */
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
	env->getsuffix_f = &ft_getsuffixbigf;
	env->normal_mask = env->normal_mask | n_suffix_mask;
	env->long_mask = env->long_mask | l_suffix_mask;
	(void)opt;
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

int		ft_gopt(t_env *env, char opt)
{
	(void)opt;
	env->long_mask = env->long_mask & ~l_uid_mask;
	return (ft_lopt(env, opt));
}

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

int		ft_nopt(t_env *env, char opt)
{
	(void)opt;
	env->uidsize_f = &ft_uididsize;
	env->uidprint_f = &ft_uididprint;
	env->gidsize_f = &ft_gididsize;
	env->gidprint_f = &ft_gididprint;
	return (ft_lopt(env, opt));
}

int		ft_oopt(t_env *env, char opt)
{
	(void)opt;
	env->long_mask = env->long_mask & ~l_gid_mask;
	return (ft_lopt(env, opt));
}

int		ft_popt(t_env *env, char opt)
{
	env->getsuffix_f = &ft_getsuffixp;
	env->normal_mask = env->normal_mask | n_suffix_mask;
	env->long_mask = env->long_mask | l_suffix_mask;
	(void)opt;
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
	env->normal_mask = env->normal_mask | n_blocks_mask;
	env->long_mask = env->long_mask | l_blocks_mask;
	env->total = 2;
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

int		ft_xopt(t_env *env, char opt)
{
	(void)opt;
	env->print_f = &ft_print_colhor;
	return (0);
}

int		ft_1opt(t_env *env, char opt)
{
	(void)opt;
	env->print_f = &ft_print_oebl;
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
