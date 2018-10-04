/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 07:34:55 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/04 07:53:59 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_ls(t_env *env)
{
	ft_config(env);
	if (ft_readargv(env))
		return (1);
	env->dirtitle_f = (env->argc > 1) ? &ft_titleddir : &ft_untitleddir;
	if (env->badargs)
		ft_badargs(env);
	if (env->fileargs)
		ft_fileargs(env);
	env->total = env->total | t_dir_mask;
	if (env->dirargs && env->explore_f(env))
		return (1);
	if (env->colortab)
		ft_freecolortab(env);
	return (0);
}

int			main(int argc, char **argv)
{
	t_env	env;

	env.argc = argc;
	env.prog_name = argv[0];
	env.argv = argv;
	if (ft_ls(&env))
		return (1);
	return (0);
}
