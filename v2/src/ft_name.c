/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_name.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 16:29:05 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/28 16:45:08 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_nameprint(t_env *env, t_file *file, int spaces)
{
	(void)spaces;
	ft_fillbuff(env, 1, file->name);
}

int			ft_namesize(t_env *env, t_file *file)
{
	char	*name;
	int		i;

	(void)env;
	name = file->name;
	i = 0;
	while (name[i])
		i++;
	return (i);
}
