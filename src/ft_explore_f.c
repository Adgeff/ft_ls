/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_explore_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 21:17:16 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/04 02:44:35 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_explore(t_env *env)
{
	t_file	*tmp;

	env->dirargs = env->sort_f(env, env->dirargs, env->cmp_f);
	while (env->dirargs)
	{
		env->dirtitle_f(env);
		if (ft_getdir(env))
			return (1);
		if (env->fileargs)
			env->fileargs = env->sort_f(env, env->fileargs, env->cmp_f);
		env->print_f(env);
		ft_freelist(env->fileargs);
		env->fileargs = NULL;
		tmp = env->dirargs;
		env->dirargs = env->dirargs->next;
		free(tmp->name);
		free(tmp->path);
		free(tmp);
		if (env->dirargs)
			ft_fillbuff_c(env, 1, '\n');
	}
	return (0);
}

int			ft_recursive_explore(t_env *env)
{
	t_file	*tmp;

	env->dirargs = env->sort_f(env, env->dirargs, env->cmp_f);
	while (env->dirargs)
	{
		env->dirtitle_f(env);
		if (ft_getdir(env))
			return (1);
		if (env->fileargs)
			env->fileargs = env->sort_f(env, env->fileargs, env->cmp_f);
		env->print_f(env);
		tmp = env->dirargs;
		env->dirargs = env->dirargs->next;
		free(tmp->name);
		free(tmp->path);
		free(tmp);
		if (env->fileargs)
			ft_addorfree(env, env->fileargs);
		env->fileargs = NULL;
		if (env->dirargs)
			ft_fillbuff_c(env, 1, '\n');
	}
	return (0);
}
