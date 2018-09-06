/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 09:34:31 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/06 21:53:59 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

size_t		ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int			ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return ((unsigned)s1[i] - (unsigned)s2[i]);
}

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

void		ft_putstr_fd(int fd, char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	write(fd, str, i);
}

void		ft_putchar_fd(int fd, char c)
{
	write(fd, &c, 1);
}
