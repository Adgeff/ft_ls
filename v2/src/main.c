/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 07:34:55 by geargenc          #+#    #+#             */
/*   Updated: 2018/06/13 18:04:39 by geargenc         ###   ########.fr       */
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
	if (!(file->name = arg) ||
		!(file->path = path))
		return (1);
	file->next = *list;
	*list = file;
	return (0);
}

int				ft_select_all(const char *file_name)
{
	(void)file_name;
	return (1);
}

int				ft_nohidden_select(const char *file_name)
{
	return (file_name[0] != '.');
}

void			ft_config(t_env *env)
{
	env->size = 0;
	env->readarg_f = &ft_defreadarg;
	env->sort_f = &ft_merge_sort;
	env->cmp_f = &ft_ascii_cmp;
	env->print_f = &ft_print_oebl;
	env->explore_f = &ft_explore;
	env->select_f = &ft_nohidden_select;
	env->badargs = NULL;
	env->fileargs = NULL;
	env->dirargs = NULL;
}

ssize_t			ft_writebuff(t_env *env)
{
	ssize_t		ret;

	ret = write(env->fd, env->buf, env->size);
	env->size = 0;
	return (ret);
}

ssize_t			ft_fillbuff_n(t_env *env, int fd, char *str, ssize_t size)
{
	ssize_t		i;
	ssize_t		j;

	if (fd != env->fd && env->size && ft_writebuff(env) < 0)
		return (-1);
	env->fd = fd;
	if (size > BUFF_SIZE)
	{
		if ((i = ft_fillbuff_n(env, fd, str, BUFF_SIZE)) < 0 ||
			(j = ft_fillbuff_n(env, fd, str + BUFF_SIZE, size - BUFF_SIZE)) < 0)
			return (-1);
		return (i + j);
	}
	j = 0;
	if (env->size + size > BUFF_SIZE && (j = ft_writebuff(env)) < 0)
		return (-1);
	i = 0;
	while (i < size)
	{
		env->buf[env->size + i] = str[i];
		i++;
	}
	env->size = env->size + size;
	return (j);
}

ssize_t			ft_fillbuff(t_env *env, int fd, char *str)
{
	ssize_t		i;

	i = 0;
	while (str[i])
		i++;
	return (ft_fillbuff_n(env, fd, str, i));
}

ssize_t			ft_fillbuff_c(t_env *env, int fd, char c)
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

	env->badargs = ft_rev_list(env->badargs, &ft_ascii_cmp);
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

void			ft_print_oebl(t_env *env)
{
	t_file		*list;

	list = env->fileargs;
	while (list)
	{
		ft_fillbuff(env, 1, list->name);
		ft_fillbuff_c(env, 1, '\n');
		list = list->next;
	}
}

void			ft_fileargs(t_env *env)
{
	env->fileargs = env->sort_f(env->fileargs, env->cmp_f);
	env->print_f(env);
	ft_freelist(env->fileargs);
	env->fileargs = NULL;
	if (env->dirargs)
		ft_fillbuff_c(env, 1, '\n');
}

char			*ft_getpath(char *dir_path, char *name)
{
	char		*path;
	char		*tmp;

	if (!(path = (char *)malloc(ft_strlen(dir_path) + ft_strlen(name) + 2)))
		return (NULL);
	tmp = ft_stpcpy(path, dir_path);
	if (path != tmp && tmp[-1] != '/')
	{
		*tmp = '/';
		tmp++;
	}
	ft_stpcpy(tmp, name);
	return (path);
}

void			ft_direrror(t_env *env)
{
	char		*error;

	error = strerror(errno);
	ft_fillbuff(env, 2, env->prog_name);
	ft_fillbuff(env, 2, ": ");
	ft_fillbuff(env, 2, env->dirargs->name);
	ft_fillbuff(env, 2, ": ");
	ft_fillbuff(env, 2, error);
	ft_fillbuff_c(env, 2, '\n');
}

int				ft_getdir(t_env *env)
{
	DIR			*dir_ptr;
	t_dirent	*file_ptr;
	t_file		*file;

	if (!(dir_ptr = opendir(env->dirargs->path)))
	{
		ft_direrror(env);
		return (0);
	}
	while ((file_ptr = readdir(dir_ptr)))
	{
		if (env->select_f(file_ptr->d_name))
		{
			if (!(file = (t_file *)malloc(sizeof(t_file))) ||
				ft_addarg(&(env->fileargs), ft_strdup(file_ptr->d_name),
				ft_getpath(env->dirargs->path, file_ptr->d_name), file))
				return (1);
			lstat(file->path, &(file->stat));
		}
	}
	closedir(dir_ptr);
	return (0);
}

int				ft_explore(t_env *env)
{
	t_file		*tmp;

	env->dirargs = env->sort_f(env->dirargs, env->cmp_f);
	while (env->dirargs)
	{
		env->dirtitle_f(env);
		if (ft_getdir(env))
			return (1);
		env->fileargs = env->sort_f(env->fileargs, env->cmp_f);
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

void			ft_addorfree(t_env *env, t_file *list)
{
	if (list->next)
		ft_addorfree(env, list->next);
	if (list->stat.st_mode & S_IFDIR && ft_strcmp(list->name, ".") &&
		ft_strcmp(list->name, ".."))
	{
		list->next = env->dirargs;
		env->dirargs = list;
	}
	else
	{
		free(list->name);
		free(list->path);
		free(list);
	}
}

int				ft_recursive_explore(t_env *env)
{
	t_file		*tmp;

	env->dirargs = env->sort_f(env->dirargs, env->cmp_f);
	while (env->dirargs)
	{
		env->dirtitle_f(env);
		if (ft_getdir(env))
			return (1);
		if (env->fileargs)
			env->fileargs = env->sort_f(env->fileargs, env->cmp_f);
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

void			ft_titleddir(t_env *env)
{
	ft_fillbuff(env, 1, env->dirargs->path);
	ft_fillbuff(env, 1, ":\n");
}

void			ft_untitleddir(t_env *env)
{
	env->dirtitle_f = &ft_titleddir;
}

int				ft_ls(t_env *env)
{
	ft_config(env);
	if (ft_readargv(env))
		return (1);
	env->dirtitle_f = (env->argc > 1) ? &ft_titleddir : &ft_untitleddir;
	if (env->badargs)
		ft_badargs(env);
	if (env->fileargs)
		ft_fileargs(env);
	if (env->dirargs && env->explore_f(env))
		return (1);
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
