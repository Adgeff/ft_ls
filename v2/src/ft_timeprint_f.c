/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_timeprint_f.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 16:36:23 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/28 16:37:17 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_longtimeprint(t_env *env, t_file *file)
{
	time_t		ftime;
	struct tm	*fstm;

	ftime = env->gettime_f(&(file->stat));
	fstm = localtime(&ftime);
	ft_daymonthprint(env, fstm);
	ft_fillbuff_c(env, 1, ' ');
	ft_hmsprint(env, fstm->tm_hour);
	ft_fillbuff_c(env, 1, ':');
	ft_hmsprint(env, fstm->tm_min);
	ft_fillbuff_c(env, 1, ':');
	ft_hmsprint(env, fstm->tm_sec);
	ft_fillbuff_c(env, 1, ' ');
	ft_yearprint(env, fstm->tm_year + 1900);
	ft_fillbuff_c(env, 1, ' ');
}

void			ft_shorttimeprint(t_env *env, t_file *file)
{
	time_t		ftime;
	struct tm	*fstm;

	ftime = env->gettime_f(&(file->stat));
	fstm = localtime(&ftime);
	ft_daymonthprint(env, fstm);
	ft_fillbuff_c(env, 1, ' ');
	if (ftime + SIXMONTHS > env->now && ftime < env->now + SIXMONTHS)
	{
		ft_hmsprint(env, fstm->tm_hour);
		ft_fillbuff_c(env, 1, ':');
		ft_hmsprint(env, fstm->tm_min);
	}
	else
	{
		ft_fillbuff_c(env, 1, ' ');
		ft_yearprint(env, fstm->tm_year + 1900);
	}
	ft_fillbuff_c(env, 1, ' ');
}
