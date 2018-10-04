/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dirtitle_f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 21:30:35 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/04 07:31:20 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_titleddir(t_env *env)
{
	int	i;

	i = 0;
	while (env->dirargs->path[i])
		i++;
	write(1, env->dirargs->path, i);
	write(1, ":\n", 2);
}

void	ft_untitleddir(t_env *env)
{
	env->dirtitle_f = &ft_titleddir;
}
