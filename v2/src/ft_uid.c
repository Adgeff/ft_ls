/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 17:10:12 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/28 17:11:03 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_uidprint(t_env *env, t_file *file, int spaces)
{
	env->uidprint_f(env, file);
	while (spaces--)
		ft_fillbuff_c(env, 1, ' ');
	ft_fillbuff(env, 1, "  ");
}

int		ft_uidsize(t_env *env, t_file *file)
{
	return (env->uidsize_f(env, file));
}
