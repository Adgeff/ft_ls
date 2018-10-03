/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_col_tools1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 20:08:49 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 20:13:24 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_col_print(t_env *env, t_colp *colp, t_file **order, int *size)
{
	int		i;
	int		j;
	int		spaces;

	j = 0;
	while (j < colp->lines)
	{
		i = 0;
		while (i < colp->maxbyline && order[j * colp->maxbyline + i])
		{
			ft_colprint(env, order[j * colp->maxbyline + i], size);
			if (i + 1 < colp->maxbyline && order[j * colp->maxbyline + i + 1])
			{
				spaces = colp->maxdatasize - ft_getfiledatasize(env,
					order[j * colp->maxbyline + i], size);
				spaces = (spaces + 7) / 8;
				while (spaces--)
					ft_fillbuff_c(env, 1, '\t');
			}
			i++;
		}
		ft_fillbuff_c(env, 1, '\n');
		j++;
	}
}

void		ft_get_colp(t_env *env, t_file *list, int *size, t_colp *colp)
{
	size[5] = 1;
	colp->listsize = ft_getlistsize(list);
	colp->maxdatasize = ft_getmaxfiledatasize(env, size);
	colp->maxdatasize = (colp->maxdatasize + 8) / 8 * 8;
	colp->maxbyline = env->ws_col / colp->maxdatasize;
	if (colp->maxbyline == 0)
		colp->maxbyline = 1;
	colp->lines = (colp->listsize + colp->maxbyline - 1) / colp->maxbyline;
	colp->total = colp->lines * colp->maxbyline;
}

int			ft_getfiledatasize(t_env *env, t_file *file, int *size)
{
	int		i;
	int		datasize;

	i = 0;
	datasize = 0;
	while (env->normal_mask >> i)
	{
		if ((env->normal_mask >> i) & 1 && ft_coldatatab(i).size)
			datasize = datasize + size[i];
		i++;
	}
	datasize = datasize - size[3] + file->size[3];
	if (env->normal_mask & n_suffix_mask)
		datasize = datasize - size[5] + file->size[5];
	return (datasize);
}

int			ft_getlistsize(t_file *list)
{
	int		i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

int			ft_getmaxfiledatasize(t_env *env, int *size)
{
	int		maxsize;
	int		i;

	maxsize = 0;
	i = 0;
	while (env->normal_mask >> i)
	{
		if ((env->normal_mask >> i) & 1 && ft_coldatatab(i).size)
			maxsize = maxsize + size[i];
		i++;
	}
	return (maxsize);
}
