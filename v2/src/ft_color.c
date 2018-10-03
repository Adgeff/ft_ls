/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 16:25:58 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/28 16:27:07 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_colorprint(t_env *env, t_file *file, int spaces)
{
	(void)spaces;
	ft_fillbuff(env, 1, ft_ftypetab((file->stat.st_mode >> 12) & 017).
		color_f(env, file->stat.st_mode)[0]);
	ft_fillbuff(env, 1, ft_ftypetab((file->stat.st_mode >> 12) & 017).
		color_f(env, file->stat.st_mode)[1]);
}

void	ft_endcolorprint(t_env *env, t_file *file, int spaces)
{
	(void)spaces;
	ft_fillbuff(env, 1, ft_ftypetab((file->stat.st_mode >> 12) & 017).
		color_f(env, file->stat.st_mode)[2]);
}
