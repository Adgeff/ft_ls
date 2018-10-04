/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lnk.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 14:38:33 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 14:41:01 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			**ft_lnkcolor(t_env *env, mode_t mode)
{
	(void)mode;
	return (env->colortab[2]);
}

char			*ft_lnksuffix(mode_t mode)
{
	static char	*all = "@";

	(void)mode;
	return (all);
}
