/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uidprint_f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 17:14:33 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/28 17:15:10 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_uididprint(t_env *env, t_file *file)
{
	uid_t			uid;
	uid_t			power;

	uid = file->stat.st_uid;
	power = 1;
	while (uid / 10 >= power)
		power *= 10;
	while (power)
	{
		ft_fillbuff_c(env, 1, uid / power % 10 + '0');
		power /= 10;
	}
}

void				ft_uidnameprint(t_env *env, t_file *file)
{
	struct passwd	*uid;

	if ((uid = getpwuid(file->stat.st_uid)))
		ft_fillbuff(env, 1, uid->pw_name);
	else
		ft_uididprint(env, file);
}
