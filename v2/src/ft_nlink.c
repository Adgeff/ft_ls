/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nlink.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 17:21:18 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/28 17:22:12 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_nlinkprint(t_env *env, t_file *file, int spaces)
{
	nlink_t	nlink;
	nlink_t	power;

	while (spaces--)
		ft_fillbuff_c(env, 1, ' ');
	nlink = file->stat.st_nlink;
	power = 1;
	while (nlink / 10 >= power)
		power *= 10;
	while (power)
	{
		ft_fillbuff_c(env, 1, nlink / power % 10 + '0');
		power /= 10;
	}
	ft_fillbuff_c(env, 1, ' ');
}

int			ft_nlinksize(t_env *env, t_file *file)
{
	nlink_t	nlink;
	int		size;

	(void)env;
	nlink = file->stat.st_nlink;
	size = 1;
	while (nlink > 9)
	{
		size++;
		nlink /= 10;
	}
	return (size);
}
