/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buff.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 09:39:59 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/27 09:59:20 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

ssize_t			ft_writebuff(t_env *env)
{
	ssize_t		ret;

	ret = write(env->fd, env->buf, env->size);
	env->size = 0;
	return (ret);
}

ssize_t			ft_fillbuff_n(t_env *env, int fd, char *str, ssize_t size)
{
	ssize_t		i;
	ssize_t		j;

	if (fd != env->fd && env->size && ft_writebuff(env) < 0)
		return (-1);
	env->fd = fd;
	if (size > BUFF_SIZE)
	{
		if ((i = ft_fillbuff_n(env, fd, str, BUFF_SIZE)) < 0 ||
			(j = ft_fillbuff_n(env, fd, str + BUFF_SIZE, size - BUFF_SIZE)) < 0)
			return (-1);
		return (i + j);
	}
	j = 0;
	if (env->size + size > BUFF_SIZE && (j = ft_writebuff(env)) < 0)
		return (-1);
	i = 0;
	while (i < size)
	{
		env->buf[env->size + i] = str[i];
		i++;
	}
	env->size = env->size + size;
	return (j);
}

ssize_t			ft_fillbuff(t_env *env, int fd, char *str)
{
	ssize_t		i;

	i = 0;
	while (str[i])
		i++;
	return (ft_fillbuff_n(env, fd, str, i));
}

ssize_t			ft_fillbuff_c(t_env *env, int fd, char c)
{
	return (ft_fillbuff_n(env, fd, &c, 1));
}
