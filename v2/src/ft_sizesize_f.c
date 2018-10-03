/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sizesize_f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 16:54:27 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/28 16:55:12 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_sizebytesize(t_env *env, t_file *file)
{
	off_t	off;
	int		size;

	(void)env;
	off = file->stat.st_size;
	size = 1;
	while (off > 9)
	{
		size++;
		off /= 10;
	}
	return (size);
}

int			ft_sizeunitsize(t_env *env, t_file *file)
{
	(void)env;
	(void)file;
	return (5);
}
