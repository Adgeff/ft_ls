/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wht.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 14:34:02 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 14:34:20 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			**ft_whtcolor(t_env *env, mode_t mode)
{
	(void)mode;
	return (env->colortab[0]);
}

char			*ft_whtsuffix(mode_t mode)
{
	static char	*all = "%";

	(void)mode;
	return (all);
}
