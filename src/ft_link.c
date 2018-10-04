/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_link.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 16:20:43 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/04 02:27:05 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_linkprint(t_env *env, t_file *file, int spaces)
{
	char	buf[1023];
	int		ret;

	(void)spaces;
	if ((ret = readlink(file->path, buf, sizeof(buf))) > 0)
	{
		buf[ret] = '\0';
		ft_fillbuff(env, 1, " -> ");
		ft_fillbuff(env, 1, buf);
	}
}
