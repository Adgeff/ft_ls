/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config_blocksize.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 19:49:43 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/04 08:03:46 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_config_blocksize(t_env *env)
{
	char	*envblksize;

	if (!(envblksize = getenv("BLOCKSIZE")))
		env->blocksize = DEF_BLOCKSIZE;
	else
		env->blocksize = ft_atoi(envblksize);
	if (env->blocksize < 512)
	{
		env->blocksize = 512;
		ft_putstr_fd(2, env->prog_name);
		ft_putstr_fd(2, ": minimum blocksize is 512\n");
	}
	else if (env->blocksize > 1073741824)
	{
		env->blocksize = 1073741824;
		ft_putstr_fd(2, env->prog_name);
		ft_putstr_fd(2, ": maximum blocksize is 1G\n");
	}
	else
		env->blocksize = env->blocksize / 512 * 512;
}
