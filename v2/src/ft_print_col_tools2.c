/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_col_tools2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 20:11:56 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 20:15:03 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_order_colhor(t_file *list, t_colp *colp, t_file **order)
{
	int		i;

	i = 0;
	while (i < colp->total)
	{
		if (list)
		{
			order[i] = list;
			list = list->next;
		}
		else
			order[i] = NULL;
		i++;
	}
}

void		ft_order_colvert(t_file *list, t_colp *colp, t_file **order)
{
	int		i;

	i = 0;
	while (i < colp->total)
	{
		if (list)
		{
			order[i % colp->lines * colp->maxbyline + i / colp->lines] = list;
			list = list->next;
		}
		else
			order[i % colp->lines * colp->maxbyline + i / colp->lines] = NULL;
		i++;
	}
}
