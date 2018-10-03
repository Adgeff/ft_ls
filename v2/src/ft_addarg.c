/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addarg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 21:15:05 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 21:15:17 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_addarg(t_file **list, char *arg, char *path, t_file *file)
{
	if (!(file->name = arg) ||
		!(file->path = path))
		return (1);
	file->next = *list;
	*list = file;
	return (0);
}
