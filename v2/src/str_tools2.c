/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 21:41:47 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 21:42:03 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*ft_strdup(const char *str)
{
	char	*dup;
	int		i;

	i = 0;
	while (str[i])
		i++;
	if (!(dup = (char *)malloc(i + 1)))
		return (NULL);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

size_t		ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char		*ft_strrchr(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	while (str[i] != c)
	{
		if (!i)
			return (NULL);
		i--;
	}
	return (str + i);
}
