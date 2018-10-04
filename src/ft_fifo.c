/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fifo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 14:50:56 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 14:51:12 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			**ft_fifocolor(t_env *env, mode_t mode)
{
	(void)mode;
	return (env->colortab[4]);
}

char			*ft_fifosuffix(mode_t mode)
{
	static char	*all = "|";

	(void)mode;
	return (all);
}
