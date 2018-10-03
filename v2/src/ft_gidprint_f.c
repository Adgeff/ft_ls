/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gidprint_f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 17:04:05 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/28 17:04:41 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_gididprint(t_env *env, t_file *file)
{
	gid_t			gid;
	gid_t			power;

	gid = file->stat.st_gid;
	power = 1;
	while (gid / 10 >= power)
		power *= 10;
	while (power)
	{
		ft_fillbuff_c(env, 1, gid / power % 10 + '0');
		power /= 10;
	}
}

void				ft_gidnameprint(t_env *env, t_file *file)
{
	struct group	*gid;

	if ((gid = getgrgid(file->stat.st_gid)))
		ft_fillbuff(env, 1, gid->gr_name);
	else
		ft_gididprint(env, file);
}
