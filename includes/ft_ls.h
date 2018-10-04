/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 07:38:41 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/04 03:24:42 by geargenc         ###   ########.fr       */
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
**						default values for env variables
*/

# define DEF_LSCOLORS	"exfxcxdxbxegedabagacad"
# define DEF_BLOCKSIZE	512

/*
**						other usefull values
*/

# define SIXMONTHS		15724800

/*
**						enums for printing masks
*/

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

/*
**						Structures
*/

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
	long				(*cmp_f)(struct s_env *, t_file *, t_file *);
	void				(*dirtitle_f)(struct s_env *env);
	int					(*explore_f)(struct s_env *env);
	char				*(*getsuffix_f)(mode_t);
	time_t				(*gettime_f)(struct stat *stat);
	void				(*gidprint_f)(struct s_env *, t_file *);
	int					(*gidsize_f)(struct s_env *, t_file *);
	void				(*print_f)(struct s_env *env);
	int					(*readarg_f)(struct s_env *, char *);
	int					(*select_f)(const char *file_name);
	void				(*sizeprint_f)(struct s_env *, t_file *);
	int					(*sizesize_f)(struct s_env *, t_file *);
	t_file				*(*sort_f)(struct s_env *, t_file *,
						long (*)(struct s_env *, t_file *, t_file *));
	int					(*stat_f)(const char *, struct stat *);
	void				(*timeprint_f)(struct s_env *, t_file *);
	void				(*uidprint_f)(struct s_env *, t_file *);
	int					(*uidsize_f)(struct s_env *, t_file *);
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
**						ft_addarg.c
**						This function adds an argument in a given list
*/

int						ft_addarg(t_file **list, char *arg, char *path,
						t_file *file);

/*
**						ft_badargs
**						Bad arguments treatment function
*/

void					ft_badargs(t_env *env);

/*
**						ft_blk.c
**						Block file colors function
*/

char					**ft_blkcolor(t_env *env, mode_t mode);

/*
**						ft_blocks.c
**						File size (in blocks) printing functions
*/

int						ft_blockssize(t_env *env, t_file *file);
void					ft_blocksprint(t_env *env, t_file *file, int spaces);

/*
**						ft_buff.c
**						Buffer functions
*/

ssize_t					ft_writebuff(t_env *env);
ssize_t					ft_fillbuff_n(t_env *env, int fd, char *str,
						ssize_t size);
ssize_t					ft_fillbuff(t_env *env, int fd, char *str);
ssize_t					ft_fillbuff_c(t_env *env, int fd, char c);

/*
**						ft_chr.c
**						Character file colors function
*/

char					**ft_chrcolor(t_env *env, mode_t mode);

/*
**						ft_cmp_f.c
**						Functions to compare files and sort them
**						(struct s_env -> cmp_f)
*/

long					ft_ascii_cmp(t_env *env, t_file *l1, t_file *l2);
long					ft_size_cmp(t_env *env, t_file *l1, t_file *l2);
long					ft_time_cmp(t_env *env, t_file *l1, t_file *l2);

/*
**						ft_color.c
**						Colors printing functions
*/

void					ft_colorprint(t_env *env, t_file *file, int spaces);
void					ft_endcolorprint(t_env *env, t_file *file, int spaces);

/*
**						ft_config_blocksize.c
**						Blocksize configuration
*/

void					ft_config_blocksize(t_env *env);

/*
**						ft_config_colorsX.c (1 <= X <= 2)
**						Colors configuration
*/

t_colorcode				ft_colorcode(int i);
int						ft_config_colors(t_env *env);
char					*ft_getback(t_env *env, int type);
char					ft_getcharcode(t_env *env, char *envcolor, int i);
void					ft_getcolorcode(t_env *env);
char					*ft_getfor(t_env *env, int type);
int						ft_init_colortab(t_env *env);

/*
**						ft_config.c
**						Initial configuration or program
*/

void					ft_config_functions(t_env *env);
void					ft_config_term(t_env *env);
void					ft_config(t_env *env);

/*
**						ft_datatab.c
**						Arrays with usefull functions for printing
**						The functions used depends of printing function
*/

t_data					ft_coldatatab(int i);
t_data					ft_longdatatab(int i);
t_data					ft_normaldatatab(int i);

/*
**						ft_dir.c
**						Directory file suffix and colors functions
*/

char					**ft_dircolor(t_env *env, mode_t mode);
char					*ft_dirsuffix(mode_t mode);

/*
**						ft_dirtitle_f.c
**						Directory title functions
**						(struct s_env -> dirtitle_f)
*/

void					ft_titleddir(t_env *env);
void					ft_untitleddir(t_env *env);

/*
**						ft_exeperm.c
**						Execution permissions functions
*/

char					ft_uidexe(mode_t mode);
char					ft_gidexe(mode_t mode);
char					ft_othersexe(mode_t mode);

/*
**						ft_explore_f.c
**						Directory exploration functions
**						(struct s_env -> explore_f)
*/

int						ft_explore(t_env *env);
int						ft_recursive_explore(t_env *env);

/*
**						ft_explore_tools.c
**						Tools for directory exploration
*/

void					ft_addorfree(t_env *env, t_file *list);
void					ft_delfile(t_env *env);
void					ft_direrror(t_env *env);
int						ft_getdir(t_env *env);
char					*ft_getpath(char *dir_path, char *name);

/*
**						ft_fifo.c
**						Fifo file suffix and colors functions
*/

char					**ft_fifocolor(t_env *env, mode_t mode);
char					*ft_fifosuffix(mode_t mode);

/*
**						ft_fileargs.c
**						Non directory arguments treatment function
*/

void					ft_fileargs(t_env *env);

/*
**						ft_freecolortab.c
**						Colortab free function
*/

void					ft_freecolortab(t_env *env);

/*
**						ft_freelist.c
**						File list free function
*/

void					ft_freelist(t_file *list);

/*
**						ft_ftypetab.c
**						Array filled with datas for each file type in this
**						order : character to print in long format,
**						function for colors, function for suffix with F option
**						and function for suffix with p option
*/

char					*ft_emptystr(mode_t mode);
t_ftype					ft_ftypetab(int i);

/*
**						ft_getsuffix_f.c
**						File suffix functions
**						(struct s_env -> getsuffix_f)
*/

char					*ft_getsuffixbigf(mode_t mode);
char					*ft_getsuffixp(mode_t mode);

/*
**						ft_gettime_f.c
**						Time getting functions
**						(struct s_env -> gettime_f)
*/

time_t					ft_getbirthtime(struct stat *stat);
time_t					ft_getatime(struct stat *stat);
time_t					ft_getmtime(struct stat *stat);
time_t					ft_getctime(struct stat *stat);

/*
**						ft_gid.c
**						File gid printing functions
*/

void					ft_gidprint(t_env *env, t_file *file, int spaces);
int						ft_gidsize(t_env *env, t_file *file);

/*
**						ft_gidprint_f.c
**						File gid printing functions
**						(struct s_env -> gidprint_f)
*/

void					ft_gididprint(t_env *env, t_file *file);
void					ft_gidnameprint(t_env *env, t_file *file);

/*
**						ft_gidsize_f.c
**						File gid functions
**						(struct s_env -> gidsize_f)
*/

int						ft_gididsize(t_env *env, t_file *file);
int						ft_gidnamesize(t_env *env, t_file *file);

/*
**						ft_inode.c
**						File inode printing functions
*/

int						ft_inodesize(t_env *env, t_file *file);
void					ft_inodeprint(t_env *env, t_file *file, int spaces);

/*
**						ft_link.c
**						Readlink printing function
*/

void					ft_linkprint(t_env *env, t_file *file, int spaces);

/*
**						ft_lnk.c
**						Link file suffix and colors functions
*/

char					**ft_lnkcolor(t_env *env, mode_t mode);
char					*ft_lnksuffix(mode_t mode);

/*
**						ft_majmin.c
**						Special files major/minor printing
*/

void					ft_majprint(t_env *env, t_file *file);
void					ft_minprint(t_env *env, t_file *file);
void					ft_majminprint(t_env *env, t_file *file);

/*
**						ft_mode.c
**						File mode printing functions
**						(type, permissions, extended attributes and ACL)
*/

void					ft_typeprint(t_env *env, t_file *file, int spaces);
void					ft_permsprint(t_env *env, t_file *file, int spaces);
void					ft_eaaclprint(t_env *env, t_file *file, int spaces);

/*
**						ft_name.c
**						File name printing functions
*/

void					ft_nameprint(t_env *env, t_file *file, int spaces);
int						ft_namesize(t_env *env, t_file *file);

/*
**						ft_nlink.c
**						File links number printing functions
*/

void					ft_nlinkprint(t_env *env, t_file *file, int spaces);
int						ft_nlinksize(t_env *env, t_file *file);

/*
**						ft_optsetX.c (1 <= X <= 6)
**						Options that the program can manage
*/

int						ft_bigaopt(t_env *env, char opt);
int						ft_bigcopt(t_env *env, char opt);
int						ft_bigfopt(t_env *env, char opt);
int						ft_biggopt(t_env *env, char opt);
int						ft_bighopt(t_env *env, char opt);
int						ft_bigpopt(t_env *env, char opt);
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
**						ft_getperm returns the corresponding char assiociated
**						to a permission and a file mode
**						Other functions are arrays filled with corresponding
**						chars in a logic way
*/

char					ft_getperm(int i, mode_t mode);
char					ft_uidgidexetab(int i);
char					ft_othersexetab(int i);
char					ft_readtab(int i);
char					ft_writetab(int i);

/*
**						ft_print_col_toolsX.c (1 <= X <= 2)
**						Tools for column printing
*/

void					ft_col_print(t_env *env, t_colp *colp, t_file **order,
						int *size);
void					ft_get_colp(t_env *env, t_file *list, int *size,
						t_colp *colp);
int						ft_getfiledatasize(t_env *env, t_file *file, int *size);
int						ft_getlistsize(t_file *list);
int						ft_getmaxfiledatasize(t_env *env, int *size);
void					ft_order_colhor(t_file *list, t_colp *colp,
						t_file **order);
void					ft_order_colvert(t_file *list, t_colp *colp,
						t_file **order);

/*
**						ft_print_f.c
**						Printing functions
**						(struct s_env -> print_f)
*/

void					ft_print_colhor(t_env *env);
void					ft_print_colvert(t_env *env);
void					ft_print_comma(t_env *env);
void					ft_print_long(t_env *env);
void					ft_print_oebl(t_env *env);

/*
**						ft_print_size.c
**						These functions get size of element for the space
**						alignment
*/

void					ft_colsize(t_env *env, t_file *list, int *size);
int						ft_getmax(t_env *env, t_file *list, int i,
						int (*f)(t_env *, t_file *));
void					ft_longsize(t_env *env, t_file *list, int *size);
void					ft_normalsize(t_env *env, t_file *list, int *size);

/*
**						ft_print.c
**						Print functions
*/

void					ft_colprint(t_env *env, t_file *file, int *size);
void					ft_longprint(t_env *env, t_file *file, int *size);
void					ft_normalprint(t_env *env, t_file *file, int *size);

/*
**						ft_readarg_f.c
**						File arguments reading function
**						(struct s_env -> readarg_f)
*/

int						ft_defreadarg(t_env *env, char *arg);
int						ft_nodirsreadarg(t_env *env, char *arg);

/*
**						ft_readargv.c
**						Arguments reading function
*/

t_opt					ft_opttab(int i);
int						ft_readargv(t_env *env);

/*
**						ft_readperm.c
**						Read permissions functions
*/

char					ft_uidread(mode_t mode);
char					ft_gidread(mode_t mode);
char					ft_othersread(mode_t mode);

/*
**						ft_reg.c
**						Regular file suffix and colors functions
*/

char					**ft_regcolor(t_env *env, mode_t mode);
char					*ft_regsuffix(mode_t mode);

/*
**						ft_select_f.c
**						File selection functions
**						(struct s_env -> select_f)
*/

int						ft_nodot_select(const char *file_name);
int						ft_nohidden_select(const char *file_name);
int						ft_select_all(const char *file_name);

/*
**						ft_size.c
**						File size printing functions
*/

void					ft_sizeprint(t_env *env, t_file *file, int spaces);
int						ft_sizesize(t_env *env, t_file *file);

/*
**						ft_sizeprint_f.c
**						File size printing functions
**						(struct s_env -> sizeprint_f)
*/

void					ft_sizebyteprint(t_env *env, t_file *file);
void					ft_sizemoreunitprint(t_env *env, off_t size,
						char *units);
void					ft_sizeunitprint(t_env *env, t_file *file);

/*
**						ft_sizesize_f.c
**						File size functions
**						(struct s_env -> sizesize_f)
*/

int						ft_sizebytesize(t_env *env, t_file *file);
int						ft_sizeunitsize(t_env *env, t_file *file);

/*
**						ft_sock.c
**						Socket file suffix and colors functions
*/

char					**ft_sockcolor(t_env *env, mode_t mode);
char					*ft_socksuffix(mode_t mode);

/*
**						ft_sort_f.c
**						Sort functions for files
**						(struct s_env -> sort_f)
*/

t_file					*ft_merge_sort_rev(t_env *env, t_file *list,
						long (*cmp)(t_env *, t_file *, t_file *));
t_file					*ft_merge_sort(t_env *env, t_file *list,
						long (*cmp)(t_env *, t_file *, t_file *));
t_file					*ft_rev_list(t_env *env, t_file *list,
						long (*cmp)(t_env *, t_file *, t_file *));

/*
**						ft_sort_tools.c
**						Tools for sort functions
*/

void					ft_moveall_to(t_file **from, t_file **to);
void					ft_moveone_to(t_file **from, t_file **to);
t_file					*ft_rev_list_loop(t_file *list);
void					ft_split_list(t_file **list, t_file **l1, t_file **l2);

/*
**						ft_suffix.c
**						File suffix printing functions
*/

void					ft_suffixprint(t_env *env, t_file *file, int spaces);
int						ft_suffixsize(t_env *env, t_file *file);

/*
**						ft_time.c
**						Time printing function
*/

void					ft_timeprint(t_env *env, t_file *file, int spaces);

/*
**						ft_timeprint_f.c
**						Time printing functions
**						(struct s_env -> timeprint_f)
*/

void					ft_longtimeprint(t_env *env, t_file *file);
void					ft_shorttimeprint(t_env *env, t_file *file);

/*
**						ft_timetools.c
**						Tool functions for time printing
*/

void					ft_daymonthprint(t_env *env, struct tm *fstm);
void					ft_hmsprint(t_env *env, int hms);
void					ft_yearprint(t_env *env, int year);

/*
**						ft_totalprint.c
**						Total blocksize printing function
*/

void					ft_totalprint(t_env *env, t_file *list);

/*
**						ft_uid.c
**						File uid printing functions
*/

void					ft_uidprint(t_env *env, t_file *file, int spaces);
int						ft_uidsize(t_env *env, t_file *file);

/*
**						ft_uidprint_f.c
**						File uid printing functions
**						(struct s_env -> uidprint_f)
*/

void					ft_uididprint(t_env *env, t_file *file);
void					ft_uidnameprint(t_env *env, t_file *file);

/*
**						ft_uidsize_f.c
**						File uid functions
**						(struct s_env -> uidsize_f)
*/

int						ft_uididsize(t_env *env, t_file *file);
int						ft_uidnamesize(t_env *env, t_file *file);

/*
**						ft_wht.c
**						Whiteout file suffix and colors functions
*/

char					**ft_whtcolor(t_env *env, mode_t mode);
char					*ft_whtsuffix(mode_t mode);

/*
**						ft_writeperm.c
**						Write permissions functions
*/

char					ft_uidwrite(mode_t mode);
char					ft_gidwrite(mode_t mode);
char					ft_otherswrite(mode_t mode);

/*
**						str_toolsX.c (1 <= X <= 2)
**						Tools for strings
*/

int						ft_atoi(char *str);
void					ft_putchar_fd(int fd, char c);
void					ft_putstr_fd(int fd, char *str);
char					*ft_stpcpy(char *dst, char *src);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strdup(const char *str);
size_t					ft_strlen(const char *str);
char					*ft_strrchr(char *str, char c);

#endif
