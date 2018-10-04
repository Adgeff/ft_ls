/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readperm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 19:53:28 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/06 21:53:45 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			ft_uidread(mode_t mode)
{
	return (ft_readtab((mode >> 8) & 01));
}

char			ft_gidread(mode_t mode)
{
	return (ft_readtab((mode >> 5) & 01));
}

char			ft_othersread(mode_t mode)
{
	return (ft_readtab((mode >> 2) & 01));
}
