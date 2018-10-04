/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config_colors1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 15:01:17 by geargenc          #+#    #+#             */
/*   Updated: 2018/10/01 15:08:04 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_colorcode				ft_colorcode(int i)
{
	static t_colorcode	colorcode[] = {
		{'a', "\033[30m", "\033[40m"},
		{'b', "\033[31m", "\033[41m"},
		{'c', "\033[32m", "\033[42m"},
		{'d', "\033[33m", "\033[43m"},
		{'e', "\033[34m", "\033[44m"},
		{'f', "\033[35m", "\033[45m"},
		{'g', "\033[36m", "\033[46m"},
		{'h', "\033[37m", "\033[47m"},
		{'A', "\033[1;30m", "\033[1;40m"},
		{'B', "\033[1;31m", "\033[1;41m"},
		{'C', "\033[1;32m", "\033[1;42m"},
		{'D', "\033[1;33m", "\033[1;43m"},
		{'E', "\033[1;34m", "\033[1;44m"},
		{'F', "\033[1;35m", "\033[1;45m"},
		{'G', "\033[1;36m", "\033[1;46m"},
		{'H', "\033[1;37m", "\033[1;47m"},
		{'x', "", ""},
		{'\0', NULL, NULL}
	};

	return (colorcode[i]);
}

int						ft_config_colors(t_env *env)
{
	int					i;

	ft_getcolorcode(env);
	if (!env->colortab && ft_init_colortab(env))
		return (1);
	env->colortab[0][0] = "";
	env->colortab[0][1] = "";
	env->colortab[0][2] = "";
	i = 1;
	while (i < 12)
	{
		env->colortab[i][0] = ft_getfor(env, i);
		env->colortab[i][1] = ft_getback(env, i);
		env->colortab[i][2] = (env->colortab[i][0][0] ||
			env->colortab[i][1][0]) ? "\033[39;49m\033[0m" : "";
		i++;
	}
	return (0);
}

char					*ft_getback(t_env *env, int type)
{
	int					i;

	i = 0;
	while (ft_colorcode(i).charcode != env->colorcode[(type - 1) * 2 + 1])
		i++;
	return (ft_colorcode(i).background);
}

char					ft_getcharcode(t_env *env, char *envcolor, int i)
{
	int					j;

	j = 0;
	while (ft_colorcode(j).charcode &&
		ft_colorcode(j).charcode != envcolor[i] &&
		ft_colorcode(j).charcode != envcolor[i] + ('a' - '0'))
		j++;
	if (ft_colorcode(j).charcode)
		return (ft_colorcode(j).charcode);
	else
	{
		ft_fillbuff(env, 2, "error: invalid character '");
		ft_fillbuff_c(env, 2, envcolor[i]);
		ft_fillbuff(env, 2, "' in LSCOLORS env var\n");
		return ('x');
	}
}

void					ft_getcolorcode(t_env *env)
{
	char				*defcolor;
	char				*envcolor;
	int					i;

	defcolor = DEF_LSCOLORS;
	if (!(envcolor = getenv("LSCOLORS")))
		envcolor = defcolor;
	i = 0;
	while (defcolor[i] && envcolor[i])
	{
		env->colorcode[i] = ft_getcharcode(env, envcolor, i);
		i++;
	}
	while (defcolor[i])
	{
		env->colorcode[i] = defcolor[i];
		i++;
	}
}
