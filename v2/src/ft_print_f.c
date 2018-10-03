/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 20:17:07 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 20:19:09 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_print_colhor(t_env *env)
{
	t_file	*list;
	int		size[6];
	t_colp	colp;
	t_file	**order;

	list = env->fileargs;
	ft_colsize(env, list, size);
	ft_get_colp(env, list, size, & colp);
	if (!(order = (t_file **)malloc(colp.total * sizeof(t_file *))))
		ft_print_oebl(env);
	else
	{
		ft_order_colhor(list, &colp, order);
		if (list && env->total & 1)
			ft_totalprint(env, list);
		ft_col_print(env, &colp, order, size);
		free(order);
	}
}

void		ft_print_colvert(t_env *env)
{
	t_file	*list;
	int		size[6];
	t_colp	colp;
	t_file	**order;

	list = env->fileargs;
	ft_colsize(env, list, size);
	ft_get_colp(env, list, size, & colp);
	if (!(order = (t_file **)malloc(colp.total * sizeof(t_file *))))
		ft_print_oebl(env);
	else
	{
		ft_order_colvert(list, &colp, order);
		if (list && env->total & 1)
			ft_totalprint(env, list);
		ft_col_print(env, &colp, order, size);
		free(order);
	}
}

void		ft_print_comma(t_env *env)
{
	t_file	*list;
	int		size[6];

	list = env->fileargs;
	ft_normalsize(env, list, size);
	while (list)
	{
		ft_normalprint(env, list, size);
		if (list->next)
			ft_fillbuff(env, 1, ", ");
		else
			ft_fillbuff_c(env, 1, '\n');
		list = list->next;
	}
}

void		ft_print_long(t_env *env)
{
	t_file	*list;
	int		size[16];

	list = env->fileargs;
	ft_longsize(env, list, size);
	if (list && env->total & 1)
		ft_totalprint(env, list);
	while (list)
	{
		ft_longprint(env, list, size);
		ft_fillbuff_c(env, 1, '\n');
		list = list->next;
	}
}

void		ft_print_oebl(t_env *env)
{
	t_file	*list;
	int		size[6];

	list = env->fileargs;
	ft_normalsize(env, list, size);
	if (list && env->total & 1)
		ft_totalprint(env, list);
	while (list)
	{
		ft_normalprint(env, list, size);
		ft_fillbuff_c(env, 1, '\n');
		list = list->next;
	}
}
