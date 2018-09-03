/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 17:19:48 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/03 13:29:10 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_ascii_cmp(t_env *env, t_file *l1, t_file *l2)
{
	(void)env;
	return (ft_strcmp(l1->name, l2->name));
}

int		ft_time_cmp(t_env *env, t_file *l1, t_file *l2)
{
	return ((env->gettime_f(&(l1->stat)) == env->gettime_f(&(l2->stat))) ?
		ft_ascii_cmp(env, l1, l2) :
		env->gettime_f(&(l2->stat)) - env->gettime_f(&(l1->stat)));
}
