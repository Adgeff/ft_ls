/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_suffix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 16:24:02 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/28 16:45:27 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_suffixprint(t_env *env, t_file *file, int spaces)
{
	(void)spaces;
	ft_fillbuff(env, 1, env->getsuffix_f(file->stat.st_mode));
}

int		ft_suffixsize(t_env *env, t_file *file)
{
	if (*env->getsuffix_f(file->stat.st_mode))
		return (1);
	else
		return (0);
}
