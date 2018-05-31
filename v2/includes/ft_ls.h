/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 07:38:41 by geargenc          #+#    #+#             */
/*   Updated: 2018/05/31 17:19:20 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H

# define FT_LS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
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
}					t_env;

typedef struct		s_opt
{
	char			opt;
	int				(*f)(t_env *, char);
}					t_opt;

/*
** str_tools.c
*/

int					ft_strcmp(const char *s1, const char *s2);
void				ft_putstr_fd(int fd, char *str);
void				ft_putchar_fd(int fd, char c);

/*
** ft_readargv.c
*/

t_opt				ft_opttab(int i);
int					ft_readargv(t_env *env);

/*
** options
*/

int					ft_topt(t_env *env, char opt);
int					ft_illegalopt(t_env *env, char opt);

#endif
