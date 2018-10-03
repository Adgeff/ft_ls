/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 14:17:10 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 14:17:42 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_inodesize(t_env *env, t_file *file)
{
	ino_t	inode;
	int		size;

	(void)env;
	inode = file->stat.st_ino;
	size = 2;
	while (inode > 9)
	{
		size++;
		inode /= 10;
	}
	return (size);
}

void		ft_inodeprint(t_env *env, t_file *file, int spaces)
{
	ino_t	inode;
	ino_t	power;

	while (spaces--)
		ft_fillbuff_c(env, 1, ' ');
	inode = file->stat.st_ino;
	power = 1;
	while (inode / 10 >= power)
		power *= 10;
	while (power)
	{
		ft_fillbuff_c(env, 1, inode / power % 10 + '0');
		power /= 10;
	}
	ft_fillbuff_c(env, 1, ' ');
}
