/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 14:11:33 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 14:12:54 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_typeprint(t_env *env, t_file *file, int spaces)
{
	(void)spaces;
	ft_fillbuff_c(env, 1, ft_ftypetab((file->stat.st_mode >> 12) & 017).lprint);
}

void		ft_permsprint(t_env *env, t_file *file, int spaces)
{
	int		i;

	(void)spaces;
	i = 0;
	while (i < 9)
	{
		ft_fillbuff_c(env, 1, ft_getperm(i, file->stat.st_mode));
		i++;
	}
}

void		ft_eaaclprint(t_env *env, t_file *file, int spaces)
{
	acl_t	acl;

	(void)spaces;
	if (listxattr(file->path, NULL, 0, 0) > 0)
		ft_fillbuff_c(env, 1, '@');
	else if ((acl = acl_get_link_np(file->path, ACL_TYPE_EXTENDED)))
	{
		ft_fillbuff_c(env, 1, '+');
		acl_free(acl);
	}
	else
		ft_fillbuff_c(env, 1, ' ');
	ft_fillbuff_c(env, 1, ' ');
}
