/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 19:53:20 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 19:58:14 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_colsize(t_env *env, t_file *list, int *size)
{
	int		i;

	i = 0;
	while (env->normal_mask >> i)
	{
		if ((env->normal_mask >> i) & 1 && ft_coldatatab(i).size)
			size[i] = ft_getmax(env, list, i, ft_coldatatab(i).size);
		i++;
	}
}

int			ft_getmax(t_env *env, t_file *list, int i,
			int (*f)(t_env *, t_file *))
{
	int		max;

	max = 0;
	while (list)
	{
		if ((list->size[i] = f(env, list)) > max)
			max = list->size[i];
		list = list->next;
	}
	return (max);
}

void		ft_longsize(t_env *env, t_file *list, int *size)
{
	int		i;

	i = 0;
	while (env->long_mask >> i)
	{
		if ((env->long_mask >> i) & 1 && ft_longdatatab(i).size)
			size[i] = ft_getmax(env, list, i, ft_longdatatab(i).size);
		i++;
	}
}

void		ft_normalsize(t_env *env, t_file *list, int *size)
{
	int		i;

	i = 0;
	while (env->normal_mask >> i)
	{
		if ((env->normal_mask >> i) & 1 && ft_normaldatatab(i).size)
			size[i] = ft_getmax(env, list, i, ft_normaldatatab(i).size);
		i++;
	}
}
