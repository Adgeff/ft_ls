/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getsuffix_f.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 14:29:24 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 14:32:06 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_getsuffixbigf(mode_t mode)
{
	return (ft_ftypetab((mode >> 12) & 017).suffixbigf_f(mode));
}

char	*ft_getsuffixp(mode_t mode)
{
	return (ft_ftypetab((mode >> 12) & 017).suffixp_f(mode));
}
