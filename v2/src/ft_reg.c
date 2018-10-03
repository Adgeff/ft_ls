/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 14:42:19 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 14:42:44 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			**ft_regcolor(t_env *env, mode_t mode)
{
	if (mode & 0111)
	{
		if (mode & S_ISUID)
			return (env->colortab[8]);
		else if (mode & S_ISGID)
			return (env->colortab[9]);
		else
			return (env->colortab[5]);
	}
	else
		return (env->colortab[0]);
}

char			*ft_regsuffix(mode_t mode)
{
	static char	*exe = "*";
	static char	*nexe = "";

	if (mode & 0111)
		return (exe);
	else
		return (nexe);
}
