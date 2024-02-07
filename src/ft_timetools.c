/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_timetools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 16:31:43 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/04 03:29:11 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_daymonthprint(t_env *env, struct tm *fstm)
{
//	if (*nl_langinfo(D_MD_ORDER) == 'd')
//	{
//		ft_fillbuff_c(env, 1, (fstm->tm_mday / 10) ?
//			fstm->tm_mday / 10 + '0' : ' ');
//		ft_fillbuff_c(env, 1, fstm->tm_mday % 10 + '0');
//		ft_fillbuff_c(env, 1, ' ');
//		ft_fillbuff(env, 1, nl_langinfo(ABMON_1 + fstm->tm_mon));
//	}
//	else
//	{
		ft_fillbuff(env, 1, nl_langinfo(ABMON_1 + fstm->tm_mon));
		ft_fillbuff_c(env, 1, ' ');
		ft_fillbuff_c(env, 1, (fstm->tm_mday / 10) ?
			fstm->tm_mday / 10 + '0' : ' ');
		ft_fillbuff_c(env, 1, fstm->tm_mday % 10 + '0');
//	}
}

void	ft_hmsprint(t_env *env, int hms)
{
	ft_fillbuff_c(env, 1, hms / 10 + '0');
	ft_fillbuff_c(env, 1, hms % 10 + '0');
}

void	ft_yearprint(t_env *env, int year)
{
	if (year / 10)
		ft_yearprint(env, year / 10);
	ft_fillbuff_c(env, 1, year % 10 + '0');
}
