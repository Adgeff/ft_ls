/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 14:46:08 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 14:46:27 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			**ft_dircolor(t_env *env, mode_t mode)
{
	if (mode & (S_ISVTX | S_IWOTH))
		return (env->colortab[10]);
	else if (mode & S_IWOTH)
		return (env->colortab[11]);
	else
		return (env->colortab[1]);
}

char			*ft_dirsuffix(mode_t mode)
{
	static char	*all = "/";

	(void)mode;
	return (all);
}
