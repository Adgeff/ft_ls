/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 16:41:18 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/28 16:42:23 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_sizeprint(t_env *env, t_file *file, int spaces)
{
	while (spaces--)
		ft_fillbuff_c(env, 1, ' ');
	if (S_ISCHR(file->stat.st_mode) || S_ISBLK(file->stat.st_mode))
		ft_majminprint(env, file);
	else
		env->sizeprint_f(env, file);
	ft_fillbuff_c(env, 1, ' ');
}

int		ft_sizesize(t_env *env, t_file *file)
{
	if (S_ISCHR(file->stat.st_mode) || S_ISBLK(file->stat.st_mode))
		return (8);
	return (env->sizesize_f(env, file));
}
