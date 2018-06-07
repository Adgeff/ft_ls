/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 07:34:55 by geargenc          #+#    #+#             */
/*   Updated: 2018/06/07 19:56:53 by geargenc         ###   ########.fr       */
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
	env->size = 0;
	env->readarg_f = &ft_defreadarg;
	env->sort_f = &ft_merge_sort;
	env->cmp_f = &ft_ascii_cmp;
	env->badargs = NULL;
	env->fileargs = NULL;
	env->dirargs = NULL;
}

void			ft_printlist(t_env *env, t_file *list)
{
	while (list)
	{
		ft_fillbuff(env, 1, list->name);
		ft_fillbuff(env, 1, " -> ");
		ft_fillbuff(env, 1, list->path);
		ft_fillbuff(env, 1, "\n");
		list = list->next;
	}
}

ssize_t			ft_writebuff(t_env *env)
{
	ssize_t		ret;

	ret = write(env->fd, env->buf, env->size);
	env->size = 0;
	return (ret);
}

int				ft_fillbuff_n(t_env *env, int fd, char *str, size_t size)
{
	size_t		i;

	if (fd != env->fd && env->size && ft_writebuff(env) < 0)
		return (1);
	env->fd = fd;
	if (size > BUFF_SIZE)
	{
		if (ft_fillbuff_n(env, fd, str, BUFF_SIZE) ||
			ft_fillbuff_n(env, fd, str + BUFF_SIZE, size - BUFF_SIZE))
			return (1);
		return (0);
	}
	if (env->size + size > BUFF_SIZE && ft_writebuff(env) < 0)
		return (1);
	i = 0;
	while (i < size)
	{
		env->buf[env->size + i] = str[i];
		i++;
	}
	env->size = env->size + size;
	return (0);
}

int				ft_fillbuff(t_env *env, int fd, char *str)
{
	size_t		i;

	i = 0;
	while (str[i])
		i++;
	return (ft_fillbuff_n(env, fd, str, i));
}

int				ft_fillbuff_c(t_env *env, int fd, char c)
{
	return (ft_fillbuff_n(env, fd, &c, 1));
}

void			ft_freelist(t_file *list)
{
	if (!list)
		return ;
	ft_freelist(list->next);
	free(list->name);
	free(list->path);
	free(list);
}

void			ft_badargs(t_env *env)
{
	t_file		*list;

	env->badargs = ft_merge_sort(env->badargs, &ft_ascii_cmp);
	list = env->badargs;
	while (list)
	{
		ft_fillbuff(env, 2, env->prog_name);
		ft_fillbuff(env, 2, ": ");
		ft_fillbuff(env, 2, list->name);
		ft_fillbuff(env, 2, ": ");
		ft_fillbuff(env, 2, list->path);
		ft_fillbuff(env, 2, "\n");
		list = list->next;
	}
	ft_freelist(env->badargs);
	env->badargs = NULL;
}

int				ft_ls(t_env *env)
{
	ft_config(env);
	if (ft_readargv(env))
		return (1);
	if (env->badargs)
		ft_badargs(env);
	if (env->fileargs)
		env->fileargs = env->sort_f(env->fileargs, env->cmp_f);
	if (env->dirargs)
		env->dirargs = env->sort_f(env->dirargs, env->cmp_f);
	ft_fillbuff(env, 1, "Files :\n");
	ft_printlist(env, env->fileargs);
	ft_fillbuff(env, 1, "Direrctories :\n");
	ft_printlist(env, env->dirargs);
	ft_writebuff(env);
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
