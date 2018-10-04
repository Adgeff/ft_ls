/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_datatab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 16:14:47 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/28 16:15:57 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_data				ft_coldatatab(int i)
{
	static t_data	normaldatatab[] = {
		{&ft_inodesize, &ft_inodeprint},
		{&ft_blockssize, &ft_blocksprint},
		{NULL, &ft_colorprint},
		{&ft_namesize, &ft_nameprint},
		{NULL, &ft_endcolorprint},
		{&ft_suffixsize, &ft_suffixprint}
	};

	return (normaldatatab[i]);
}

t_data				ft_longdatatab(int i)
{
	static t_data	longdatatab[] = {
		{&ft_inodesize, &ft_inodeprint},
		{&ft_blockssize, &ft_blocksprint},
		{NULL, &ft_typeprint},
		{NULL, &ft_permsprint},
		{NULL, &ft_eaaclprint},
		{&ft_nlinksize, &ft_nlinkprint},
		{&ft_uidsize, &ft_uidprint},
		{&ft_gidsize, &ft_gidprint},
		{NULL, NULL},
		{&ft_sizesize, &ft_sizeprint},
		{NULL, &ft_timeprint},
		{NULL, &ft_colorprint},
		{NULL, &ft_nameprint},
		{NULL, &ft_endcolorprint},
		{NULL, &ft_suffixprint},
		{NULL, &ft_linkprint}
	};

	return (longdatatab[i]);
}

t_data				ft_normaldatatab(int i)
{
	static t_data	normaldatatab[] = {
		{&ft_inodesize, &ft_inodeprint},
		{&ft_blockssize, &ft_blocksprint},
		{NULL, &ft_colorprint},
		{NULL, &ft_nameprint},
		{NULL, &ft_endcolorprint},
		{NULL, &ft_suffixprint}
	};

	return (normaldatatab[i]);
}
