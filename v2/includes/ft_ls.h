/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 07:38:41 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/20 14:51:45 by geargenc         ###   ########.fr       */
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
# include <sys/acl.h>
# include <sys/xattr.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <locale.h>
# include <langinfo.h>
# include <sys/ioctl.h>

/*
**							default values for env variables
*/

# define DEF_LSCOLORS		"exfxcxdxbxegedabagacad"
# define DEF_BLOCKSIZE		512
# define SIXMONTHS			15724800

typedef enum			e_n_mask
{
	n_inode_mask = 0x00000001,
	n_blocks_mask = 0x00000002,
	n_colorstart_mask = 0x00000004,
	n_name_mask = 0x00000008,
	n_colorend_mask = 0x00000010,
	n_suffix_mask = 0x00000020,

	n_color_mask = (n_colorstart_mask | n_colorend_mask),
	n_def_mask = (n_name_mask)
}						t_n_mask;

typedef enum			e_l_mask
{
	l_inode_mask = 0x00000001,
	l_blocks_mask = 0x00000002,
	l_type_mask = 0x00000004,
	l_perms_mask = 0x00000008,
	l_eaacl_mask = 0x00000010,
	l_nlink_mask = 0x00000020,
	l_uid_mask = 0x00000040,
	l_gid_mask = 0x00000080,
	l_flag_mask = 0x00000100,
	l_size_mask = 0x00000200,
	l_time_mask = 0x00000400,
	l_colorstart_mask = 0x00000800,
	l_name_mask = 0x00001000,
	l_colorend_mask = 0x00002000,
	l_suffix_mask = 0x00004000,
	l_link_mask = 0x00008000,

	l_mode_mask = (l_type_mask | l_perms_mask | l_eaacl_mask),
	l_color_mask = (l_colorstart_mask | l_colorend_mask),
	l_def_mask = (l_mode_mask | l_nlink_mask | l_uid_mask | l_gid_mask |
		l_size_mask | l_time_mask | l_name_mask | l_link_mask)
}						t_l_mask;

typedef struct dirent	t_dirent;

typedef struct			s_file
{
	char				*name;
	char				*path;
	int					size[16];
	struct passwd		*uid;
	struct group		*gid;
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
	int					ws_col;
	int					total;
	t_n_mask			normal_mask;
	t_l_mask			long_mask;
	char				***colortab;
	char				colorcode[22];
	long long			blocksize;
	time_t				now;
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
	int					(*uidsize_f)(struct s_env *, t_file *);
	void				(*uidprint_f)(struct s_env *, t_file *);
	int					(*gidsize_f)(struct s_env *, t_file *);
	void				(*gidprint_f)(struct s_env *, t_file *);
	int					(*sizesize_f)(struct s_env *, t_file *);
	void				(*sizeprint_f)(struct s_env *, t_file *);
	void				(*timeprint_f)(struct s_env *, t_file *);
}						t_env;

typedef struct			s_ftype
{
	char				lprint;
	char				**(*color_f)(t_env *env, mode_t);
	char				*(*suffixbigf_f)(mode_t);
	char				*(*suffixp_f)(mode_t);
}						t_ftype;

typedef struct			s_colorcode
{
	char				charcode;
	char				*foreground;
	char				*background;
}						t_colorcode;

typedef struct			s_opt
{
	char				opt;
	int					(*f)(t_env *, char);
}						t_opt;

typedef struct			s_data
{
	int					(*size)(t_env *, t_file *);
	void				(*print)(t_env *, t_file *, int);
}						t_data;

typedef struct			s_colp
{
	int					listsize;
	int					maxdatasize;
	int					lines;
	int					maxbyline;
	int					total;					
}						t_colp;

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
int						ft_bigcopt(t_env *env, char opt);
int						ft_bigfopt(t_env *env, char opt);
int						ft_biggopt(t_env *env, char opt);
int						ft_bigropt(t_env *env, char opt);
int						ft_bigsopt(t_env *env, char opt);
int						ft_bigtopt(t_env *env, char opt);
int						ft_biguopt(t_env *env, char opt);
int						ft_aopt(t_env *env, char opt);
int						ft_copt(t_env *env, char opt);
int						ft_dopt(t_env *env, char opt);
int						ft_fopt(t_env *env, char opt);
int						ft_gopt(t_env *env, char opt);
int						ft_hopt(t_env *env, char opt);
int						ft_iopt(t_env *env, char opt);
int						ft_kopt(t_env *env, char opt);
int						ft_lopt(t_env *env, char opt);
int						ft_mopt(t_env *env, char opt);
int						ft_nopt(t_env *env, char opt);
int						ft_oopt(t_env *env, char opt);
int						ft_popt(t_env *env, char opt);
int						ft_ropt(t_env *env, char opt);
int						ft_sopt(t_env *env, char opt);
int						ft_topt(t_env *env, char opt);
int						ft_uopt(t_env *env, char opt);
int						ft_xopt(t_env *env, char opt);
int						ft_1opt(t_env *env, char opt);
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

void					ft_print_colhor(t_env *env);
void					ft_print_colvert(t_env *env);
int						ft_uididsize(t_env *env, t_file *file);
void					ft_uididprint(t_env *env, t_file *file);
int						ft_gididsize(t_env *env, t_file *file);
void					ft_gididprint(t_env *env, t_file *file);
int						ft_sizeunitsize(t_env *env, t_file *file);
void					ft_sizeunitprint(t_env *env, t_file *file);
void					ft_longtimeprint(t_env *env, t_file *file);
void					ft_print_long(t_env *env);
void					ft_config_blocksize(t_env *env);
t_ftype					ft_ftypetab(int i);
char					*ft_getsuffixbigf(mode_t mode);
char					*ft_getsuffixp(mode_t mode);
int						ft_config_colors(t_env *env);
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
