/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 16:11:22 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/28 16:12:24 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_nodot_select(const char *file_name)
{
	return (ft_strcmp(file_name, ".") && ft_strcmp(file_name, ".."));
}

int		ft_nohidden_select(const char *file_name)
{
	return (file_name[0] != '.');
}

int		ft_select_all(const char *file_name)
{
	(void)file_name;
	return (1);
}
