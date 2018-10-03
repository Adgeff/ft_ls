/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_blocks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 14:25:45 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 14:26:01 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				ft_blockssize(t_env *env, t_file *file)
{
	blkcnt_t	blocks;
	int			size;
	
	blocks = (file->stat.st_blocks * 512 + (env->blocksize - 1))
		/ env->blocksize;
	size = 2;
	while (blocks > 9)
	{
		size++;
		blocks /= 10;
	}
	return (size);
}

void			ft_blocksprint(t_env *env, t_file *file, int spaces)
{
	blkcnt_t	blocks;
	blkcnt_t	power;

	while (spaces--)
		ft_fillbuff_c(env, 1, ' ');
	blocks = (file->stat.st_blocks * 512 + (env->blocksize - 1))
		/ env->blocksize;
	power = 1;
	while (blocks / 10 >= power)
		power *= 10;
	while (power)
	{
		ft_fillbuff_c(env, 1, blocks / power % 10 + '0');
		power /= 10;
	}
	ft_fillbuff_c(env, 1, ' ');
}
