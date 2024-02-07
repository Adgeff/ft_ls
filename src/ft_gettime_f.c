/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gettime_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 10:00:05 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/27 10:00:18 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

time_t			ft_getatime(struct stat *stat)
{
	return (stat->st_atime);
}

time_t			ft_getmtime(struct stat *stat)
{
	return (stat->st_mtime);
}

time_t			ft_getctime(struct stat *stat)
{
	return (stat->st_ctime);
}
