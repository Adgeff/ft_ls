/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sizeprint_f.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 16:46:28 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/28 16:47:54 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_sizebyteprint(t_env *env, t_file *file)
{
	off_t	off;
	off_t	power;

	off = file->stat.st_size;
	power = 1;
	while (off / 10 >= power)
		power *= 10;
	while (power)
	{
		ft_fillbuff_c(env, 1, off / power % 10 + '0');
		power /= 10;
	}
}

void		ft_sizemoreunitprint(t_env *env, off_t size, char *units)
{
	off_t	u;
	off_t	d;

	d = size % 1024 * 1000 / 1024;
	u = size / 1024;
	u = u + (u > 9 ? d > 499 : d > 949);
	d = (d + 50) / 100 % 10;
	if (u > 999)
		ft_sizemoreunitprint(env, size / 1024, units + 1);
	else if (u > 9)
	{
		ft_fillbuff_c(env, 1, (u > 99) ? u / 100 + '0' : ' ');
		ft_fillbuff_c(env, 1, u / 10 % 10 + '0');
		ft_fillbuff_c(env, 1, u % 10 + '0');
		ft_fillbuff_c(env, 1, *units);
	}
	else
	{
		ft_fillbuff_c(env, 1, u + '0');
		ft_fillbuff_c(env, 1, '.');
		ft_fillbuff_c(env, 1, d + '0');
		ft_fillbuff_c(env, 1, *units);
	}
}

void		ft_sizeunitprint(t_env *env, t_file *file)
{
	off_t	u;

	ft_fillbuff_c(env, 1, ' ');
	u = file->stat.st_size;
	if (u > 999)
		ft_sizemoreunitprint(env, u, "KMGTP");
	else
	{
		ft_fillbuff_c(env, 1, (u > 99) ? u / 100 + '0' : ' ');
		ft_fillbuff_c(env, 1, (u > 9) ? u / 10 % 10 + '0' : ' ');
		ft_fillbuff_c(env, 1, u % 10 + '0');
		ft_fillbuff_c(env, 1, 'B');
	}
}
