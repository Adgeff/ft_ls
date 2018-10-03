/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uidsize_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 17:16:59 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 14:19:13 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					ft_uididsize(t_env *env, t_file *file)
{
	uid_t			uid;
	int				size;

	(void)env;
	uid = file->stat.st_uid;
	size = 1;
	while (uid > 9)
	{
		size++;
		uid /= 10;
	}
	return (size);
}

int					ft_uidnamesize(t_env *env, t_file *file)
{
	struct passwd	*uid;
	int				size;

	(void)env;
	if (!(uid = getpwuid(file->stat.st_uid)))
		return (ft_uididsize(env, file));
	size = 0;
	while (uid->pw_name[size])
		size++;
	return (size);
}
