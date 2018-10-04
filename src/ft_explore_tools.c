/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_explore_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 21:09:51 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/04 07:43:40 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_addorfree(t_env *env, t_file *list)
{
	if (list->next)
		ft_addorfree(env, list->next);
	if (S_ISDIR(list->stat.st_mode) && ft_strcmp(list->name, ".") &&
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

void			ft_delfile(t_env *env)
{
	t_file		*file;

	file = env->fileargs;
	env->fileargs = env->fileargs->next;
	free(file->name);
	free(file->path);
	free(file);
}

void			ft_direrror(t_env *env)
{
	char		*error;

	error = strerror(errno);
	ft_putstr_fd(2, env->prog_name);
	ft_putstr_fd(2, ": ");
	ft_putstr_fd(2, env->dirargs->name);
	ft_putstr_fd(2, ": ");
	ft_putstr_fd(2, error);
	ft_putchar_fd(2, '\n');
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
			if (lstat(file->path, &(file->stat)))
				ft_delfile(env);
		}
	}
	closedir(dir_ptr);
	return (0);
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
