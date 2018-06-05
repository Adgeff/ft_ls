/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readarg_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 17:43:31 by geargenc          #+#    #+#             */
/*   Updated: 2018/06/05 18:09:23 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				ft_defreadarg(t_env *env, char *arg)
{
	t_file		*file;

	if (!(file = (t_file *)malloc(sizeof(t_file))))
		return (1);
	if (lstat(arg, &(file->stat)))
	{
		if (ft_addarg(&(env->badargs), arg, strerror(errno), file))
			return (1);
	}
	else
	{
		if ((file->stat.st_mode & S_IFDIR) ?
			ft_addarg(&(env->dirargs), arg, arg, file) :
			ft_addarg(&(env->fileargs), arg, arg, file))
			return (1);
	}
	return (0);
}

int				ft_nodirsreadarg(t_env *env, char *arg)
{
	t_file		*file;

	if (!(file = (t_file *)malloc(sizeof(t_file))))
		return (1);
	if (lstat(arg, &(file->stat)))
	{
		if (ft_addarg(&(env->badargs), arg, strerror(errno), file))
			return (1);
	}
	else if (ft_addarg(&(env->fileargs), arg, arg, file))
		return (1);
	return (0);
}
