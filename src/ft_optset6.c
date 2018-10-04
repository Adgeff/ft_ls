/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optset6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 02:34:57 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/04 08:42:57 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_topt(t_env *env, char opt)
{
	(void)opt;
	env->cmp_f = &ft_time_cmp;
	return (0);
}

int		ft_uopt(t_env *env, char opt)
{
	(void)opt;
	env->gettime_f = &ft_getatime;
	return (0);
}

int		ft_xopt(t_env *env, char opt)
{
	(void)opt;
	env->print_f = &ft_print_colhor;
	env->link_arg = env->link_arg | la_enable_mask;
	return (0);
}

int		ft_1opt(t_env *env, char opt)
{
	(void)opt;
	env->print_f = &ft_print_oebl;
	env->link_arg = env->link_arg | la_enable_mask;
	return (0);
}

int		ft_illegalopt(t_env *env, char opt)
{
	int	i;

	ft_putstr_fd(2, env->prog_name);
	ft_putstr_fd(2, ": illegal option -- ");
	ft_putchar_fd(2, opt);
	ft_putstr_fd(2, "\nusage: ");
	ft_putstr_fd(2, env->prog_name);
	ft_putstr_fd(2, " [-");
	i = 0;
	while (ft_opttab(i).opt)
	{
		ft_putchar_fd(2, ft_opttab(i).opt);
		i++;
	}
	ft_putstr_fd(2, "] [file ...]\n");
	return (1);
}
