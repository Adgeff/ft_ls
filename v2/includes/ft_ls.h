/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 07:38:41 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/09 22:30:02 by geargenc         ###   ########.fr       */
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
# include <dirent.h>
# include <time.h>

# define DEF_COLORCODE "exfxcxdxbxegedabagacad"

typedef struct dirent	t_dirent;

typedef struct			s_vsize
{
	int					lnnum;
	int					uid;
	int					gid;
	int					size;
}						t_vsize;

typedef struct			s_file
{
	char				*name;
	char				*path;
	t_vsize				vsize;
	struct stat			stat;
	struct s_file		*next;
}						t_file;

typedef struct			s_env
{
	char				*prog_name;
	char				**argv;
	int					argc;
	char				buf[BUFF_SIZE];
	int					fd;
	ssize_t				size;
	int					total;
	int					normal_mask;
	int					long_mask;
	char				***colortab;
	char				*colorcode;
	t_file				*badargs;
	t_file				*fileargs;
	t_file				*dirargs;
	int					(*readarg_f)(struct s_env *, char *);
	t_file				*(*sort_f)(struct s_env *, t_file *,
						int (*)(struct s_env *, t_file *, t_file *));
	int					(*cmp_f)(struct s_env *, t_file *, t_file *);
	void				(*print_f)(struct s_env *env);
	int					(*explore_f)(struct s_env *env);
	void				(*dirtitle_f)(struct s_env *env);
	int					(*select_f)(const char *file_name);
	time_t				(*gettime_f)(struct stat *stat);
	char				*(*getsuffix_f)(mode_t);
}						t_env;

typedef struct			s_opt
{
	char				opt;
	int					(*f)(t_env *, char);
}						t_opt;

/*
**						ft_comp.c
*/

int						ft_ascii_cmp(t_env *env, t_file *l1, t_file *l2);
int						ft_size_cmp(t_env *env, t_file *l1, t_file *l2);
int						ft_time_cmp(t_env *env, t_file *l1, t_file *l2);

/*
**						ft_exeperm.c
*/

char					ft_uidexe(mode_t mode);
char					ft_gidexe(mode_t mode);
char					ft_othersexe(mode_t mode);

/*
**						ft_merge_sort.c
*/

t_file					*ft_merge_sort_rev(t_env *env, t_file *list,
						int (*cmp)(t_env *, t_file *, t_file *));
t_file					*ft_merge_sort(t_env *env, t_file *list,
						int (*cmp)(t_env *, t_file *, t_file *));

/*
**						ft_no_sort.c
*/

t_file					*ft_rev_list(t_env *env, t_file *list,
						int (*cmp)(t_env *, t_file *, t_file *));

/*
**						options
*/

int						ft_bigaopt(t_env *env, char opt);
int						ft_bigropt(t_env *env, char opt);
int						ft_bigsopt(t_env *env, char opt);
int						ft_biguopt(t_env *env, char opt);
int						ft_aopt(t_env *env, char opt);
int						ft_copt(t_env *env, char opt);
int						ft_dopt(t_env *env, char opt);
int						ft_fopt(t_env *env, char opt);
int						ft_mopt(t_env *env, char opt);
int						ft_ropt(t_env *env, char opt);
int						ft_topt(t_env *env, char opt);
int						ft_uopt(t_env *env, char opt);
int						ft_illegalopt(t_env *env, char opt);

/*
**						ft_permtabs.c
*/

char					ft_getperm(int i, mode_t mode);
char					ft_uidgidexetab(int i);
char					ft_othersexetab(int i);
char					ft_readtab(int i);
char					ft_writetab(int i);

/*
**						ft_readarg_f.c
*/

int						ft_defreadarg(t_env *env, char *arg);
int						ft_nodirsreadarg(t_env *env, char *arg);

/*
**						ft_readargv.c
*/

t_opt					ft_opttab(int i);
int						ft_readargv(t_env *env);

/*
**						ft_readperm.c
*/

char					ft_uidread(mode_t mode);
char					ft_gidread(mode_t mode);
char					ft_othersread(mode_t mode);

/*
**						ft_writeperm.c
*/

char					ft_uidwrite(mode_t mode);
char					ft_gidwrite(mode_t mode);
char					ft_otherswrite(mode_t mode);

/*
**						str_tools.c
*/

size_t					ft_strlen(const char *str);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strdup(const char *str);
void					ft_putstr_fd(int fd, char *str);
void					ft_putchar_fd(int fd, char c);
char					*ft_strrchr(char *str, char c);

/*
**						others
*/

int						ft_addarg(t_file **list, char *arg,
						char *path, t_file *file);
ssize_t					ft_writebuff(t_env *env);
ssize_t					ft_fillbuff_n(t_env *env, int fd, char *str,
						ssize_t size);
ssize_t					ft_fillbuff(t_env *env, int fd, char *str);
ssize_t					ft_fillbuff_c(t_env *env, int fd, char c);
void					ft_print_oebl(t_env *env);
void					ft_print_comma(t_env *env);
int						ft_explore(t_env *env);
int						ft_nohidden_select(const char *file_name);
int						ft_select_all(const char *file_name);
int						ft_nodot_select(const char *file_name);
int						ft_recursive_explore(t_env *env);
time_t					ft_getbirthtime(struct stat *stat);
time_t					ft_getatime(struct stat *stat);
time_t					ft_getmtime(struct stat *stat);
time_t					ft_getctime(struct stat *stat);

#endif
