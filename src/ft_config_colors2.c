/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config_colors2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 15:06:10 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 15:08:01 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*ft_getfor(t_env *env, int type)
{
	int		i;

	i = 0;
	while (ft_colorcode(i).charcode != env->colorcode[(type - 1) * 2])
		i++;
	return (ft_colorcode(i).foreground);
}

int			ft_init_colortab(t_env *env)
{
	int		i;

	if (!(env->colortab = (char ***)malloc(12 * sizeof(char **))))
		return (1);
	i = 0;
	while (i < 12)
	{
		if (!(env->colortab[i] = (char **)malloc(3 * sizeof(char *))))
			return (1);
		i++;
	}
	return (0);
}
