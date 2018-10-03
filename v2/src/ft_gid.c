/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 17:01:05 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/28 17:01:46 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_gidprint(t_env *env, t_file *file, int spaces)
{
	env->gidprint_f(env, file);
	while (spaces--)
		ft_fillbuff_c(env, 1, ' ');
	ft_fillbuff(env, 1, "  ");
}

int		ft_gidsize(t_env *env, t_file *file)
{
	return (env->gidsize_f(env, file));
}
