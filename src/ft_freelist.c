/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freelist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 21:03:22 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 21:03:34 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_freelist(t_file *list)
{
	if (!list)
		return ;
	ft_freelist(list->next);
	free(list->name);
	free(list->path);
	free(list);
}
