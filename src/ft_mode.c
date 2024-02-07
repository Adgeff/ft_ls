/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 14:11:33 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/04 03:58:25 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_typeprint(t_env *env, t_file *file, int spaces)
{
	(void)spaces;
	ft_fillbuff_c(env, 1, ft_ftypetab((file->stat.st_mode >> 12) & 017).lprint);
}

void		ft_permsprint(t_env *env, t_file *file, int spaces)
{
	int		i;

	(void)spaces;
	i = 0;
	while (i < 9)
	{
		ft_fillbuff_c(env, 1, ft_getperm(i, file->stat.st_mode));
		i++;
	}
}
