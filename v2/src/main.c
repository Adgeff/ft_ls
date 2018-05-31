/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 07:34:55 by geargenc          #+#    #+#             */
/*   Updated: 2018/05/31 17:20:25 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				ft_defreadarg(t_env *env, char *arg)
{
	t_file		*file;
	int			errsv;

	if (!(file = (t_file *)malloc(sizeof(t_file))))
		return (1);
	if (lstat(arg, &(file->stat)))
		ft_filepush(&(env->
}

void			ft_config(t_env *env)
{
	env->readarg_f = &ft_defreadarg;
	env->badargs = NULL;
	env->fileargs = NULL;
	env->dirargs = NULL;
}

int				ft_topt(t_env *env, char opt)
{
	(void)opt;
	(void)env;
	printf("Lecture option %c\n", opt);
	return (0);
}

int				ft_illegalopt(t_env *env, char opt)
{
	int			i;

	ft_putstr_fd(2, env->prog_name);
	ft_putstr_fd(2, ": illegal option -- ");
	write(2, &opt, 1);
	ft_putstr_fd(2, "\nusage: ");
	ft_putstr_fd(2, env->prog_name);
	ft_putstr_fd(2, " [-");
	i = 0;
	while (ft_opttab(i).opt)
	{
		ft_putchar_fd(2, ft_opttab(i).opt);
		i++;
	}
	ft_putstr_fd(2, "] [file ...]\n");
	return (1);
}

int				ft_ls(t_env *env)
{
	ft_config(env);
	if (ft_readargv(env))
		return (1);
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