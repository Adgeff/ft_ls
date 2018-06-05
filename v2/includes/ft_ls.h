/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 07:38:41 by geargenc          #+#    #+#             */
/*   Updated: 2018/06/05 18:34:17 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H

# define FT_LS_H

# define BUFF_SIZE 4096

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>

typedef struct		s_file
{
	char			*name;
	char			*path;
	struct stat		stat;
	struct s_file	*next;
}					t_file;

typedef struct		s_env
{
	char			*prog_name;
	char			**argv;
	int				argc;
	t_file			*badargs;
	t_file			*fileargs;
	t_file			*dirargs;
	int				(*readarg_f)(struct s_env *, char *);
	t_file			*(*sort_f)(t_file *list, int (*f)(t_file *, t_file *));
	int				(*cmp_f)(t_file *, t_file *);
}					t_env;

typedef struct		s_opt
{
	char			opt;
	int				(*f)(t_env *, char);
}					t_opt;

/*
**					ft_comp.c
*/

int					ft_ascii_cmp(t_file *l1, t_file *l2);

/*
**					ft_merge_sort.c
*/

t_file				*ft_merge_sort_rev(t_file *list,
					int (*f)(t_file *, t_file *));
t_file				*ft_merge_sort(t_file *list,
					int (*f)(t_file *, t_file *));

/*
**					ft_readarg_f.c
*/

int					ft_defreadarg(t_env *env, char *arg);
int					ft_nodirsreadarg(t_env *env, char *arg);

/*
**					ft_readargv.c
*/

t_opt				ft_opttab(int i);
int					ft_readargv(t_env *env);

/*
**					str_tools.c
*/

int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strdup(const char *str);
void				ft_putstr_fd(int fd, char *str);
void				ft_putchar_fd(int fd, char c);

/*
**					options
*/

int					ft_dopt(t_env *env, char opt);
int					ft_ropt(t_env *env, char opt);
int					ft_illegalopt(t_env *env, char opt);

/*
**					others
*/

int					ft_addarg(t_file **list, char *arg,
					char *path, t_file *file);

#endif
