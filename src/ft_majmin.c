/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_majmin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 16:51:23 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/28 16:52:01 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_majprint(t_env *env, t_file *file)
{
	dev_t	maj;
	dev_t	power;

	maj = major(file->stat.st_rdev);
	power = 1;
	while (maj / 10 >= power)
		power *= 10;
	if (power < 100)
		ft_fillbuff_c(env, 1, ' ');
	if (power < 10)
		ft_fillbuff_c(env, 1, ' ');
	while (power)
	{
		ft_fillbuff_c(env, 1, maj / power % 10 + '0');
		power /= 10;
	}
}

void		ft_minprint(t_env *env, t_file *file)
{
	dev_t	min;
	dev_t	power;

	min = minor(file->stat.st_rdev);
	power = 1;
	while (min / 10 >= power)
		power *= 10;
	if (power < 100)
		ft_fillbuff_c(env, 1, ' ');
	if (power < 10)
		ft_fillbuff_c(env, 1, ' ');
	while (power)
	{
		ft_fillbuff_c(env, 1, min / power % 10 + '0');
		power /= 10;
	}
}

void		ft_majminprint(t_env *env, t_file *file)
{
	ft_majprint(env, file);
	ft_fillbuff(env, 1, ", ");
	ft_minprint(env, file);
}
