/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 07:34:55 by geargenc          #+#    #+#             */
/*   Updated: 2018/06/05 18:34:16 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			*ft_stpcpy(char *dst, char *src)
{
	while (*src)
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
	return (dst);
}

int				ft_addarg(t_file **list, char *arg, char *path, t_file *file)
{
	if (!(file->name = ft_strdup(arg)) ||
		!(file->path = ft_strdup(path)))
		return (1);
	file->next = *list;
	*list = file;
	return (0);
}

void			ft_config(t_env *env)
{
	env->readarg_f = &ft_defreadarg;
	env->sort_f = &ft_merge_sort;
	env->cmp_f = &ft_ascii_cmp;
	env->badargs = NULL;
	env->fileargs = NULL;
	env->dirargs = NULL;
}

void			ft_printlist(t_file *list)
{
	while (list)
	{
		ft_putstr_fd(1, list->name);
		ft_putstr_fd(1, " -> ");
		ft_putstr_fd(1, list->path);
		ft_putstr_fd(1, "\n");
		list = list->next;
	}
}

int				ft_ls(t_env *env)
{
	ft_config(env);
	if (ft_readargv(env))
		return (1);
	if (env->badargs)
		env->badargs = ft_merge_sort(env->badargs, &ft_ascii_cmp);
	if (env->fileargs)
		env->fileargs = env->sort_f(env->fileargs, env->cmp_f);
	if (env->dirargs)
		env->dirargs = env->sort_f(env->dirargs, env->cmp_f);
	ft_putstr_fd(1, "Bad args :\n");
	ft_printlist(env->badargs);
	ft_putstr_fd(1, "Files :\n");
	ft_printlist(env->fileargs);
	ft_putstr_fd(1, "Direrctories :\n");
	ft_printlist(env->dirargs);
	return (0);
}

int				main(int argc, char **argv)
{
	t_env		env;

	env.argc = argc;
	env.prog_name = argv[0];
	env.argv = argv;
	if (ft_ls(&env))
		return (1);
	return (0);
}
