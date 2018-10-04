/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftypetab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 14:53:35 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 15:09:50 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char				*ft_emptystr(mode_t mode)
{
	(void)mode;
	return ("");
}

t_ftype				ft_ftypetab(int i)
{
	static t_ftype	ftypetab[] = {
		{'\0', NULL, NULL, NULL},
		{'p', &ft_fifocolor, &ft_fifosuffix, &ft_emptystr},
		{'c', &ft_chrcolor, &ft_emptystr, &ft_emptystr},
		{'\0', NULL, NULL, NULL},
		{'d', &ft_dircolor, &ft_dirsuffix, &ft_dirsuffix},
		{'\0', NULL, NULL, NULL},
		{'b', &ft_blkcolor, &ft_emptystr, &ft_emptystr},
		{'\0', NULL, NULL, NULL},
		{'-', &ft_regcolor, &ft_regsuffix, &ft_emptystr},
		{'\0', NULL, NULL, NULL},
		{'l', &ft_lnkcolor, &ft_lnksuffix, &ft_emptystr},
		{'\0', NULL, NULL, NULL},
		{'s', &ft_sockcolor, &ft_socksuffix, &ft_emptystr},
		{'\0', NULL, NULL, NULL},
		{'-', &ft_whtcolor, &ft_whtsuffix, &ft_emptystr}
	};

	return (ftypetab[i]);
}
