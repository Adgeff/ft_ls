/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 10:02:40 by geargenc          #+#    #+#             */
/*   Updated: 2018/05/16 14:07:40 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_config(t_env *env)
{
//	struct stat		buf;

	env->explore_f = &ft_defexplore;
	env->select_f = &ft_nohidden_select;
	env->sort_f = &ft_merge_sort;
	env->comp_f = &ft_ascii_cmp;
	/*fstat(1, &buf);
	env->print_f = ((buf.st_mode & S_IFCHR) ? &ft_print_vertcols :
		&ft_print_oebl);*/
	env->print_f = &ft_print_oebl;
	env->getname_f = &ft_defname;
	env->getnamesuffix_f = NULL;
	env->readarg_f = &ft_defread;
	env->dirs_nbr = 0;
	env->badargs = NULL;
	env->files = NULL;
	env->dirs = NULL;
}

void				ft_putstr_fd(int fd, char *str)
{
	int				i;

	i = 0;
	while (str[i])
		i++;
	write(fd, str, i);
}

t_opt *ft_opttab(void)
{
	static t_opt opttab[] = {
		//	{'R', &ft_bigropt},
		//	{'a', &ft_aopt},
		//	{'l', &ft_lopt},
		//	{'r', &ft_ropt},
		//	{'t', &ft_topt},
		{'\0', &ft_illegalopt}};

	return (opttab);
}

int					ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int					ft_ascii_cmp(t_flist *l1, t_flist *l2)
{
	return (ft_strcmp(l1->name, l2->name));
}

int					ft_illegalopt(char opt, t_env *env)
{
	int				i;

	ft_putstr_fd(2, env->prog_name);
	ft_putstr_fd(2, ": illegal option -- ");
	write(2, &opt, 1);
	ft_putstr_fd(2, "\nusage: ");
	ft_putstr_fd(2, env->prog_name);
	ft_putstr_fd(2, " [-");
	i = 0;
	while (ft_opttab()[i].opt)
	{
		write(2, &(ft_opttab()[i].opt), 1);
		i++;
	}
	ft_putstr_fd(2, "] [file ...]\n");
	return (1);
}

int					ft_readopt(char opt, t_env *env)
{
	int				i;

	i = 0;
	while (ft_opttab()[i].opt && ft_opttab()[i].opt != opt)
		i++;
	return (ft_opttab()[i].f(opt, env));
}

void				ft_flist_push_front(t_flist **begin_list, t_flist *new)
{
	new->next = *begin_list;
	*begin_list = new;
}

char				*ft_strdup(const char *s1)
{
	size_t			i;
	char			*s2;

	i = 0;
	while (s1[i])
		i++;
	if (!(s2 = (char *)malloc(i + 1)))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char				*ft_strjoin(const char *s1, const char *s2)
{
	char			*join;
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	if (!(join = (char *)malloc(i + j + 1)))
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		join[i] = s1[i];
	while (s2[++j])
		join[i + j] = s2[j];
	join[i + j] = '\0';
	return (join);
}

char				*ft_defname(t_flist *list, t_env *env)
{
	return (env->getnamesuffix_f ?
		ft_strjoin(list->name, env->getnamesuffix_f(list, env)) :
		ft_strdup(list->name));
}

int					ft_defread(char *arg, t_env *env)
{
	t_flist			*list;

	if (!(list = (t_flist *)malloc(sizeof(t_flist))) ||
		!(list->name = ft_strdup(arg)) ||
		!(list->path = ft_strdup(arg)))
	{
		perror(NULL);
		return (1);
	}
	list->errsv = 0;
	if (stat(arg, &(list->stat)))
	{
		list->errsv = errno;
		ft_flist_push_front(&(env->badargs), list);
	}
	else if (list->stat.st_mode & S_IFDIR)
		ft_flist_push_front(&(env->dirs), list);
	else
		ft_flist_push_front(&(env->files), list);
	if (!(list->dspname = env->getname_f(list, env)))
	{
		perror(NULL);
		return (1);
	}
	return (0);
}

int					ft_readargs(int argc, char **argv, t_env *env)
{
	int				i;
	int				j;

	i = 1;
	while (i < argc && argv[i][0] == '-' && argv[i][1] && strcmp(argv[i], "--"))
	{
		j = 1;
		while (argv[i][j])
		{
			if (ft_readopt(argv[i][j], env))
				return (1);
			j++;
		}
		i++;
	}
	if (i < argc && !strcmp(argv[i], "--"))
		i++;
	while (i < argc)
	{
		if (env->readarg_f(argv[i], env))
			return (1);
		env->dirs_nbr++;
		i++;
	}
	return (0);
}

void				ft_print_errors(t_flist *errors, char *prog_name)
{
	t_flist			*tmp;

	while (errors)
	{
		tmp = errors;
		errors = errors->next;
		ft_putstr_fd(2, prog_name);
		ft_putstr_fd(2, ": ");
		errno = tmp->errsv;
		perror(tmp->name);
	}
}

void				ft_freeflist(t_flist *list)
{
	t_flist			*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->name);
		free(tmp->dspname);
		free(tmp->path);
		free(tmp);
	}
}

void				ft_badargstreatment(t_env *env)
{
	env->badargs = ft_merge_sort(env->badargs, &ft_ascii_cmp);
	ft_print_errors(env->badargs, env->prog_name);
	ft_freeflist(env->badargs);
	env->badargs = NULL;
}

void				ft_print_oebl(t_flist *list, t_env *env)
{
	(void)env;
	while (list)
	{
		ft_putstr_fd(1, list->name);
		write(1, "\n", 1);
		list = list->next;
	}
}

void				ft_flistfreeone(t_flist *list)
{
	free(list->name);
	free(list->dspname);
	free(list->path);
	free(list);
}

char				*ft_getpath(char *dir_path, char *name)
{
	char			*path;
	int				i;
	int				j;

	i = 0;
	j = 0;
	while ((dir_path[i] && ++i) || (name[j] && ++j));
	if (!(path = (char *)malloc(i + j + 2)))
		return (NULL);
	i = 0;
	while (dir_path[i])
	{
		path[i] = dir_path[i];
		i++;
	}
	path[i++] = '/';
	j = 0;
	while (name[j])
	{
		path[i + j] = name[j];
		j++;
	}
	path[i + j] = '\0';
	return (path);
}

int					ft_nohidden_select(struct dirent *dirent_ptr)
{
	if (dirent_ptr->d_name[0] == '.')
		return (0);
	return (1);
}

t_flist				*ft_getfile(struct dirent *dirent, char *dir_path,
					t_env *env)
{
	t_flist			*list;

	if (!(list = (t_flist *)malloc(sizeof(t_flist))) ||
		!(list->name = ft_strdup(dirent->d_name)) ||
		!(list->path = ft_getpath(dir_path, dirent->d_name)))
		return (NULL);
	stat(list->path, &(list->stat));
	if (!(list->dspname = env->getname_f(list, env)))
		return (NULL);
	return (list);
}

t_flist				*ft_getdir(t_flist *dir, t_env *env)
{
	DIR				*dir_ptr;
	struct dirent	*dirent_ptr;
	t_flist			*list;
	t_flist			*new;

	list = NULL;
	if (!(dir_ptr = opendir(dir->path)))
		return (NULL);
	while ((dirent_ptr = readdir(dir_ptr)))
	{
		if (env->select_f(dirent_ptr))
		{
			if (!(new = ft_getfile(dirent_ptr, dir->path, env)))
				return (NULL);
			new->next = list;
			list = new;
		}
	}
	return (list);
}

int					ft_defexplore(t_env *env)
{
	t_flist			*tmp;

	if (env->files)
	{
		env->print_f(env->files, env);
		ft_freeflist(env->files);
		env->files = NULL;
		if (env->dirs)
			write(1, "\n", 1);
	}
	else
	{
		tmp = env->dirs;
		env->dirs = env->dirs->next;
		if (!(env->files = ft_getdir(tmp, env)))
			{
				perror(NULL);
				return (1);
			}
		env->files = env->sort_f(env->files, env->comp_f);
		ft_putstr_fd(1, tmp->path);
		write(1, ":\n", 2);
		ft_flistfreeone(tmp);
	}
	return (0);
}

int					ft_treatment(t_env *env)
{
	if (env->badargs)
		ft_badargstreatment(env);
	env->files = (env->files) ? env->sort_f(env->files, env->comp_f) : NULL;
	env->dirs = (env->dirs) ? env->sort_f(env->dirs, env->comp_f) : NULL;
	while (env->files || env->dirs)
		if (env->explore_f(env))
			return (1);
	return (0);
}

int					main(int argc, char **argv)
{
	t_env			env;

	env.prog_name = (argc > 0) ? argv[0] : "ft_ls";
	ft_config(&env);
	if (ft_readargs(argc, argv, &env) ||
		(!env.badargs && !env.files && !env.dirs && env.readarg_f(".", &env)) ||
		ft_treatment(&env))
		return (1);
	return (0);
}