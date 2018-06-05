/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optset1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 17:38:04 by geargenc          #+#    #+#             */
/*   Updated: 2018/06/05 18:06:59 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_dopt(t_env *env, char opt)
{
	(void)opt;
	env->readarg_f = &ft_nodirsreadarg;
	return (0);
}

int		ft_ropt(t_env *env, char opt)
{
	(void)opt;
	env->sort_f = &ft_merge_sort_rev;
	return (0);
}

int		ft_illegalopt(t_env *env, char opt)
{
	int	i;

	ft_putstr_fd(2, env->prog_name);
	ft_putstr_fd(2, ": illegal option -- ");
	write(2, &opt, 1);
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
