/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writeperm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 19:54:48 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/06 21:53:43 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			ft_uidwrite(mode_t mode)
{
	return (ft_writetab((mode >> 7) & 01));
}

char			ft_gidwrite(mode_t mode)
{
	return (ft_writetab((mode >> 4) & 01));
}

char			ft_otherswrite(mode_t mode)
{
	return (ft_writetab((mode >> 1) & 01));
}
