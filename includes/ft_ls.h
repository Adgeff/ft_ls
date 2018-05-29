/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 10:02:59 by geargenc          #+#    #+#             */
/*   Updated: 2018/05/16 13:59:41 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H

# define FT_LS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>

typedef struct		s_flist
{
	char			*name;
	char			*dspname;
	char			*path;
	int				errsv;
	struct stat		stat;
	struct s_flist	*next;
}					t_flist;

typedef struct		s_env
{
	char			*prog_name;
	int				(*explore_f)(struct s_env *);
	int				(*select_f)(struct dirent *);
	t_flist			*(*sort_f)(t_flist *, int (*)(t_flist *, t_flist *));
	int				(*comp_f)(t_flist *, t_flist *);
	void			(*print_f)(t_flist *, struct s_env *);
	char			*(*getname_f)(t_flist *, struct s_env *);
	char			*(*getnamesuffix_f)(t_flist *, struct s_env *);
	int				(*readarg_f)(char *, struct s_env *);
	int				dirs_nbr;
	t_flist			*badargs;
	t_flist			*files;
	t_flist			*dirs;
}					t_env;

typedef struct		s_opt
{
	char			opt;
	int				(*f)(char, t_env *);
}					t_opt;

int					ft_illegalopt(char opt, t_env *env);
void				ft_split_list(t_flist **list, t_flist **l1, t_flist **l2);
void				ft_moveall_to(t_flist **from, t_flist **to);
void				ft_moveone_to(t_flist **from, t_flist **to);
t_flist				*ft_merge_sort_rev(t_flist *list, int (*f)(t_flist *,
					t_flist *));
t_flist				*ft_merge_sort(t_flist *list, int (*f)(t_flist *,
					t_flist *));
int					ft_ascii_cmp(t_flist *l1, t_flist *l2);
int					ft_defread(char *arg, t_env *env);
void				ft_print_oebl(t_flist *list, t_env *);
char				*ft_defname(t_flist *list, t_env *env);
int					ft_defexplore(t_env *env);
int					ft_nohidden_select(struct dirent *dirent_ptr);

#endif
