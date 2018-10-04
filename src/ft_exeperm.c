/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exeperm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 20:03:19 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/06 21:53:37 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			ft_uidexe(mode_t mode)
{
	return (ft_uidgidexetab(((mode >> 6) & 01) | ((mode >> 10) & 02)));
}

char			ft_gidexe(mode_t mode)
{
	return (ft_uidgidexetab(((mode >> 3) & 01) | ((mode >> 9) & 02)));
}

char			ft_othersexe(mode_t mode)
{
	return (ft_othersexetab((mode & 01) | ((mode >> 8) & 02)));
}
