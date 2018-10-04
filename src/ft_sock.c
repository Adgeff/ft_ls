/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sock.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 14:36:24 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 14:36:41 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			**ft_sockcolor(t_env *env, mode_t mode)
{
	(void)mode;
	return (env->colortab[3]);
}

char			*ft_socksuffix(mode_t mode)
{
	static char	*all = "=";

	(void)mode;
	return (all);
}
