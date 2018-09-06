/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_permtabs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 19:35:12 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/06 21:53:38 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			ft_getperm(int i, mode_t mode)
{
	static char	(*permtab[])(mode_t) = {
		&ft_uidread,
		&ft_uidwrite,
		&ft_uidexe,
		&ft_gidread,
		&ft_gidwrite,
		&ft_gidexe,
		&ft_othersread,
		&ft_otherswrite,
		&ft_othersexe
	};

	return (permtab[i](mode));
}

char			ft_uidgidexetab(int i)
{
	static char	uidgidexetab[] = {
		'-',
		'x',
		'S',
		's'
	};

	return (uidgidexetab[i]);
}

char			ft_othersexetab(int i)
{
	static char	othersexetab[] = {
		'-',
		'x',
		'T',
		't'
	};

	return (othersexetab[i]);
}

char			ft_readtab(int i)
{
	static char	readtab[] = {
		'-',
		'r'
	};

	return (readtab[i]);
}

char			ft_writetab(int i)
{
	static char	writetab[] = {
		'-',
		'w'
	};

	return (writetab[i]);
}
