/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gidsize_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 17:07:02 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/28 17:07:34 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					ft_gididsize(t_env *env, t_file *file)
{
	gid_t			gid;
	int				size;

	(void)env;
	gid = file->stat.st_gid;
	size = 1;
	while (gid > 9)
	{
		size++;
		gid /= 10;
	}
	return (size);
}

int					ft_gidnamesize(t_env *env, t_file *file)
{
	struct group	*gid;
	int				size;

	(void)env;
	if (!(gid = getgrgid(file->stat.st_gid)))
		return (ft_gididsize(env, file));
	size = 0;
	while (gid->gr_name[size])
		size++;
	return (size);
}
