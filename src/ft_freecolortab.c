/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freecolortab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 21:33:59 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 21:34:14 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_freecolortab(t_env *env)
{
	int		i;

	i = 0;
	while (i < 12)
	{
		free(env->colortab[i]);
		i++;
	}
	free(env->colortab);
	env->colortab = NULL;
}
