/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dirtitle_f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 21:30:35 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 21:30:55 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_titleddir(t_env *env)
{
	ft_fillbuff(env, 1, env->dirargs->path);
	ft_fillbuff(env, 1, ":\n");
}

void	ft_untitleddir(t_env *env)
{
	env->dirtitle_f = &ft_titleddir;
}
