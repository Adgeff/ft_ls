/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 19:58:51 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 19:59:44 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_colprint(t_env *env, t_file *file, int *size)
{
	int		i;

	i = 0;
	while (env->normal_mask >> i)
	{
		if ((env->normal_mask >> i) & 1)
			ft_coldatatab(i).print(env, file, size[i] - file->size[i]);
		i++;
	}
}

void		ft_longprint(t_env *env, t_file *file, int *size)
{
	int		i;

	i = 0;
	while (env->long_mask >> i)
	{
		if ((env->long_mask >> i) & 1)
			ft_longdatatab(i).print(env, file, size[i] - file->size[i]);
		i++;
	}
}

void		ft_normalprint(t_env *env, t_file *file, int *size)
{
	int		i;

	i = 0;
	while (env->normal_mask >> i)
	{
		if ((env->normal_mask >> i) & 1)
			ft_normaldatatab(i).print(env, file, size[i] - file->size[i]);
		i++;
	}
}
