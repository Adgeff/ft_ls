/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_totalprint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 20:21:25 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 20:21:41 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_totalprint(t_env *env, t_file *list)
{
	blkcnt_t	total;
	blkcnt_t	power;

	total = 0;
	while (list)
	{
		total = total + list->stat.st_blocks;
		list = list->next;
	}
	total = (total * 512 + (env->blocksize - 1)) / env->blocksize;
	ft_fillbuff(env, 1, "total ");
	power = 1;
	while (total / 10 >= power)
		power *= 10;
	while (power)
	{
		ft_fillbuff_c(env, 1, total / power % 10 + '0');
		power /= 10;
	}
	ft_fillbuff_c(env, 1, '\n');
}
