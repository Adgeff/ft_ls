/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fileargs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 21:07:14 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/04 02:39:53 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_fileargs(t_env *env)
{
	env->fileargs = env->sort_f(env, env->fileargs, env->cmp_f);
	env->print_f(env);
	ft_freelist(env->fileargs);
	env->fileargs = NULL;
	if (env->dirargs)
		ft_fillbuff_c(env, 1, '\n');
}
