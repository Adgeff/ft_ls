/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 07:34:55 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/09 22:32:43 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

typedef struct	s_ftype
{
	char		lprint;
	char		**(*color_f)(t_env *env, mode_t);
	char		*(*suffixbigf_f)(mode_t);
	char		*(*suffixp_f)(mode_t);
	void		(*size_f)(t_env *env, t_file *file);
}				t_ftype;

typedef struct	s_colorcode
{
	char		charcode;
	char		*foreground;
	char		*background;
}				t_colorcode;

t_colorcode				ft_colorcode(int i)
{
	static t_colorcode	colorcode[] = {
		{'a', "\033[30m", "\033[40m"},
		{'b', "\033[31m", "\033[41m"},
		{'c', "\033[32m", "\033[42m"},
		{'d', "\033[33m", "\033[43m"},
		{'e', "\033[34m", "\033[44m"},
		{'f', "\033[35m", "\033[45m"},
		{'g', "\033[36m", "\033[46m"},
		{'h', "\033[37m", "\033[47m"},
		{'A', "\033[1;30m", "\033[1;40m"},
		{'B', "\033[1;31m", "\033[1;41m"},
		{'C', "\033[1;32m", "\033[1;42m"},
		{'D', "\033[1;33m", "\033[1;43m"},
		{'E', "\033[1;34m", "\033[1;44m"},
		{'F', "\033[1;35m", "\033[1;45m"},
		{'G', "\033[1;36m", "\033[1;46m"},
		{'H', "\033[1;37m", "\033[1;47m"},
		{'x', "", ""},
		{'\0', NULL, NULL}
	};

	return (colorcode[i]);
}

char			*ft_getfor(t_env *env, int type)
{
	int			i;

	i = 0;
	while (ft_colorcode(i).charcode != env->colorcode[(type - 1) * 2])
		i++;
	return (ft_colorcode(i).foreground);
}

char			*ft_getback(t_env *env, int type)
{
	int			i;

	i = 0;
	while (ft_colorcode(i).charcode != env->colorcode[(type - 1) * 2 + 1])
		i++;
	return (ft_colorcode(i).background);
}

int				ft_check_colorcode(char *colorcode)
{
	int			i;

	i = 0;
	while (colorcode[i])
		i++;
	if (i != 22)
		return (1);
	while (*colorcode)
	{
		i = 0;
		while (ft_colorcode(i).charcode &&
			ft_colorcode(i).charcode != *colorcode)
			i++;
		if (!ft_colorcode(i).charcode)
			return (1);
		colorcode++;
	}
	return (0);
}

int				ft_init_colortab(t_env *env)
{
	int			i;

	if (!(env->colortab = (char ***)malloc(12 * sizeof(char **))))
		return (1);
	i = 0;
	while (i < 12)
	{
		if (!(env->colortab[i] = (char **)malloc(3 * sizeof(char *))))
			return (1);
	}
	return (0);
}

int				ft_config_colors(t_env *env)
{
	int			i;

	env->colorcode = getenv("LSCOLORS");
	if (ft_check_colorcode(env->colorcode))
		env->colorcode = DEF_COLORCODE;
	if (!env->colortab && ft_init_colortab(env))
		return (1);
	env->colortab[0][0] = "";
	env->colortab[0][1] = "";
	env->colortab[0][2] = "";
	i = 1;
	while (i < 12)
	{
		env->colortab[i][0] = ft_getfor(env, i);
		env->colortab[i][1] = ft_getback(env, i);
		env->colortab[i][2] = (env->colortab[i][0][0] ||
			env->colortab[i][1][0]) ? "\033[0m" : "";
		i++;
	}
	return (0);
}

int				ft_biggopt(t_env *env, char opt)
{
	if (ft_config_colors(env))
		return (1);
	env->normal_mask = env->normal_mask | 0x0000000a;
	env->long_mask = env->long_mask | 0x00000014;
	(void)opt;
	return (0);
}

int				ft_bigfopt(t_env *env, char opt)
{
	env->getsuffix_f = &ft_getsuffixbigf;
	env->normal_mask = env->normal_mask | 0x00000001;
	env->long_mask = env->long_mask | 0x00000002;
	(void)opt;
	return (0);
}

int				ft_popt(t_env *env, char opt)
{
	env->getsuffix_f = &ft_getsuffixp;
	env->normal_mask = env->normal_mask | 0x00000001;
	env->long_mask = env->long_mask | 0x00000002;
	(void)opt;
	return (0);
}

char			*ft_emptystr(mode_t mode)
{
	(void)mode;
	return ("");
}

char			**ft_fifocolor(t_env *env, mode_t mode)
{
	(void)mode;
	return (env->colortab[4]);
}

char			*ft_fifosuffixbigf(mode_t mode)
{
	static char	*all = "|";

	(void)mode;
	return (all);
}

char			**ft_chrcolor(t_env *env, mode_t mode)
{
	(void)mode;
	return (env->colortab[7]);
}

char			**ft_dircolor(t_env *env, mode_t mode)
{
	if (mode & (S_ISVTX | S_IWOTH))
		return (env->colortab[10]);
	else if (mode & S_IWOTH)
		return (env->colortab[11]);
	else
		return (env->colortab[1]);
}

char			*ft_dirsuffixbigf(mode_t mode)
{
	static char	*all = "/";

	(void)mode;
	return (all);
}

char			*ft_dirsuffixp(mode_t mode)
{
	static char	*all = "/";

	(void)mode;
	return (all);
}

char			**ft_blkcolor(t_env *env, mode_t mode)
{
	(void)mode;
	return (env->colortab[6]);
}

char			**ft_regcolor(t_env *env, mode_t mode)
{
	if (mode & 0111)
	{
		if (mode & S_ISUID)
			return (env->colortab[8]);
		else if (mode & S_ISGID)
			return (env->colortab[9]);
		else
			return (env->colortab[5]);
	}
	else
		return (env->colortab[0]);
}

char			*ft_regsuffixbigf(mode_t mode)
{
	static char	*exe = "*";
	static char	*nexe = "";

	if (mode & 0111)
		return (exe);
	else
		return (nexe);
}

char			**ft_lnkcolor(t_env *env, mode_t mode)
{
	(void)mode;
	return (env->colortab[2]);
}

char			*ft_lnksuffixbigf(mode_t mode)
{
	static char	*all = "@";

	(void)mode;
	return (all);
}

char			**ft_sockcolor(t_env *env, mode_t mode)
{
	(void)mode;
	return (env->colortab[3]);
}

char			*ft_socksuffixbigf(mode_t mode)
{
	static char	*all = "=";

	(void)mode;
	return (all);
}

char			**ft_whtcolor(t_env *env, mode_t mode)
{
	(void)mode;
	return (env->colortab[0]);
}

char			*ft_whtsuffixbigf(mode_t mode)
{
	static char	*all = "%";

	(void)mode;
	return (all);
}

void			ft_octsize(t_env *env, t_file *file)
{
	(void)env;
	(void)file;
}

void			ft_majmin(t_env *env, t_file *file)
{
	(void)env;
	(void)file;
}

t_ftype				ft_ftypetab(int i)
{
	static t_ftype	ftypetab[] = {
		{'\0', NULL, NULL, NULL, NULL},
		{'p', &ft_fifocolor, &ft_fifosuffixbigf, &ft_emptystr, &ft_octsize},
		{'c', &ft_chrcolor, &ft_emptystr, &ft_emptystr, &ft_majmin},
		{'\0', NULL, NULL, NULL, NULL},
		{'d', &ft_dircolor, &ft_dirsuffixbigf, &ft_dirsuffixp, &ft_octsize},
		{'\0', NULL, NULL, NULL, NULL},
		{'b', &ft_blkcolor, &ft_emptystr, &ft_emptystr, &ft_majmin},
		{'\0', NULL, NULL, NULL, NULL},
		{'-', &ft_regcolor, &ft_regsuffixbigf, &ft_emptystr, &ft_octsize},
		{'\0', NULL, NULL, NULL, NULL},
		{'l', &ft_lnkcolor, &ft_lnksuffixbigf, &ft_emptystr, &ft_octsize},
		{'\0', NULL, NULL, NULL, NULL},
		{'s', &ft_sockcolor, &ft_socksuffixbigf, &ft_emptystr, &ft_octsize},
		{'\0', NULL, NULL, NULL, NULL},
		{'-', &ft_whtcolor, &ft_whtsuffixbigf, &ft_emptystr, &ft_octsize}
	};

	return (ftypetab[i]);
}

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

int				ft_nohidden_select(const char *file_name)
{
	return (file_name[0] != '.');
}

int				ft_select_all(const char *file_name)
{
	(void)file_name;
	return (1);
}

int				ft_nodot_select(const char *file_name)
{
	return (ft_strcmp(file_name, ".") && ft_strcmp(file_name, ".."));
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
	env->gettime_f = &ft_getmtime;
	env->total = 0;
	env->normal_mask = 0x00000004;
	env->long_mask = 0x00000f69;
	env->colortab = NULL;
	env->badargs = NULL;
	env->fileargs = NULL;
	env->dirargs = NULL;
}

time_t			ft_getbirthtime(struct stat *stat)
{
	return (stat->st_birthtime);
}

time_t			ft_getatime(struct stat *stat)
{
	return (stat->st_atime);
}

time_t			ft_getmtime(struct stat *stat)
{
	return (stat->st_mtime);
}

time_t			ft_getctime(struct stat *stat)
{
	return (stat->st_ctime);
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

	env->badargs = ft_rev_list(env, env->badargs, &ft_ascii_cmp);
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

void			ft_getperms(t_env *env, mode_t mode)
{
	int			i;

	i = 0;
	while (i < 9)
	{
		ft_fillbuff_c(env, 1, ft_getperm(i, mode));
		i++;
	}
}

void			ft_print_oebl(t_env *env)
{
	t_file		*list;

	list = env->fileargs;
	while (list)
	{
		ft_getperms(env, list->stat.st_mode);
		ft_fillbuff_c(env, 1, ' ');
		ft_fillbuff(env, 1, list->name);
		ft_fillbuff_c(env, 1, '\n');
		list = list->next;
	}
}

void			ft_print_comma(t_env *env)
{
	t_file		*list;

	list = env->fileargs;
	while (list)
	{
		ft_fillbuff(env, 1, list->name);
		if (list->next)
			ft_fillbuff(env, 1, ", ");
		else
			ft_fillbuff_c(env, 1, '\n');
		list = list->next;
	}
}

/*void			ft_print_long(t_env *env)
{
	t_file		*list;
	t_szdt		max;
	int			i;

}*/

void			ft_fileargs(t_env *env)
{
	env->fileargs = env->sort_f(env, env->fileargs, env->cmp_f);
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
	env->total = 1;
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
