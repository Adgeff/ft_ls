/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readarg_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 17:43:31 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/06 21:53:57 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				ft_defreadarg(t_env *env, char *arg)
{
	t_file		*file;
	char		*name;

	name = ft_strrchr(arg, '/');
	name = name ? name + 1 : arg;
	if (!(file = (t_file *)malloc(sizeof(t_file))))
		return (1);
	if (stat(arg, &(file->stat)))
	{
		if (ft_addarg(&(env->badargs), ft_strdup(arg),
			ft_strdup(strerror(errno)), file))
			return (1);
	}
	else
	{
		if ((file->stat.st_mode & S_IFDIR) ?
			ft_addarg(&(env->dirargs), ft_strdup(name), ft_strdup(arg), file) :
			ft_addarg(&(env->fileargs), ft_strdup(arg), ft_strdup(arg), file))
			return (1);
	}
	return (0);
}

int				ft_nodirsreadarg(t_env *env, char *arg)
{
	t_file		*file;

	if (!(file = (t_file *)malloc(sizeof(t_file))))
		return (1);
	if (stat(arg, &(file->stat)))
	{
		if (ft_addarg(&(env->badargs), ft_strdup(arg),
			ft_strdup(strerror(errno)), file))
			return (1);
	}
	else if (ft_addarg(&(env->fileargs), ft_strdup(arg), ft_strdup(arg), file))
		return (1);
	return (0);
}
