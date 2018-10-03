/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_link.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 16:20:43 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/28 16:22:05 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_linkprint(t_env *env, t_file *file, int spaces)
{
	char	buf[1023];

	(void)spaces;
	if (S_ISLNK(file->stat.st_mode))
	{
		ft_fillbuff(env, 1, " -> ");
		buf[readlink(file->path, buf, sizeof(buf))] = '\0';
		ft_fillbuff(env, 1, buf);
	}
}
