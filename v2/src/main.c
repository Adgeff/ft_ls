/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 07:34:55 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/16 19:48:32 by geargenc         ###   ########.fr       */
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

char			*ft_getfor(t_env *env, int type)
{
	int			i;

	i = 0;
	while (ft_colorcode(i).charcode != env->colorcode[(type - 1) * 2])
		i++;
	return (ft_colorcode(i).foreground);
}

char			*ft_getback(t_env *env, int type)
{
	int			i;

	i = 0;
	while (ft_colorcode(i).charcode != env->colorcode[(type - 1) * 2 + 1])
		i++;
	return (ft_colorcode(i).background);
}

char			ft_getcharcode(t_env *env, char *envcolor, int i)
{
	int			j;

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

void			ft_getcolorcode(t_env *env)
{
	char		*defcolor;
	char		*envcolor;
	int			i;

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

int				ft_init_colortab(t_env *env)
{
	int			i;

	if (!(env->colortab = (char ***)malloc(12 * sizeof(char **))))
		return (1);
	i = 0;
	while (i < 12)
	{
		if (!(env->colortab[i] = (char **)malloc(3 * sizeof(char *))))
			return (1);
		i++;
	}
	return (0);
}

int				ft_config_colors(t_env *env)
{
	int			i;

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

char			*ft_emptystr(mode_t mode)
{
	(void)mode;
	return ("");
}

char			**ft_fifocolor(t_env *env, mode_t mode)
{
	(void)mode;
	return (env->colortab[4]);
}

char			*ft_fifosuffix(mode_t mode)
{
	static char	*all = "|";

	(void)mode;
	return (all);
}

char			**ft_chrcolor(t_env *env, mode_t mode)
{
	(void)mode;
	return (env->colortab[7]);
}

char			**ft_dircolor(t_env *env, mode_t mode)
{
	if (mode & (S_ISVTX | S_IWOTH))
		return (env->colortab[10]);
	else if (mode & S_IWOTH)
		return (env->colortab[11]);
	else
		return (env->colortab[1]);
}

char			*ft_dirsuffix(mode_t mode)
{
	static char	*all = "/";

	(void)mode;
	return (all);
}

char			**ft_blkcolor(t_env *env, mode_t mode)
{
	(void)mode;
	return (env->colortab[6]);
}

char			**ft_regcolor(t_env *env, mode_t mode)
{
	if (mode & 0111)
	{
		if (mode & S_ISUID)
			return (env->colortab[8]);
		else if (mode & S_ISGID)
			return (env->colortab[9]);
		else
			return (env->colortab[5]);
	}
	else
		return (env->colortab[0]);
}

char			*ft_regsuffix(mode_t mode)
{
	static char	*exe = "*";
	static char	*nexe = "";

	if (mode & 0111)
		return (exe);
	else
		return (nexe);
}

char			**ft_lnkcolor(t_env *env, mode_t mode)
{
	(void)mode;
	return (env->colortab[2]);
}

char			*ft_lnksuffix(mode_t mode)
{
	static char	*all = "@";

	(void)mode;
	return (all);
}

char			**ft_sockcolor(t_env *env, mode_t mode)
{
	(void)mode;
	return (env->colortab[3]);
}

char			*ft_socksuffix(mode_t mode)
{
	static char	*all = "=";

	(void)mode;
	return (all);
}

char			**ft_whtcolor(t_env *env, mode_t mode)
{
	(void)mode;
	return (env->colortab[0]);
}

char			*ft_whtsuffix(mode_t mode)
{
	static char	*all = "%";

	(void)mode;
	return (all);
}

t_ftype				ft_ftypetab(int i)
{
	static t_ftype	ftypetab[] = {
		{'\0', NULL, NULL, NULL},
		{'p', &ft_fifocolor, &ft_fifosuffix, &ft_emptystr},
		{'c', &ft_chrcolor, &ft_emptystr, &ft_emptystr},
		{'\0', NULL, NULL, NULL},
		{'d', &ft_dircolor, &ft_dirsuffix, &ft_dirsuffix},
		{'\0', NULL, NULL, NULL},
		{'b', &ft_blkcolor, &ft_emptystr, &ft_emptystr},
		{'\0', NULL, NULL, NULL},
		{'-', &ft_regcolor, &ft_regsuffix, &ft_emptystr},
		{'\0', NULL, NULL, NULL},
		{'l', &ft_lnkcolor, &ft_lnksuffix, &ft_emptystr},
		{'\0', NULL, NULL, NULL},
		{'s', &ft_sockcolor, &ft_socksuffix, &ft_emptystr},
		{'\0', NULL, NULL, NULL},
		{'-', &ft_whtcolor, &ft_whtsuffix, &ft_emptystr}
	};

	return (ftypetab[i]);
}

char			*ft_getsuffixbigf(mode_t mode)
{
	return (ft_ftypetab((mode >> 12) & 017).suffixbigf_f(mode));
}

char			*ft_getsuffixp(mode_t mode)
{
	return (ft_ftypetab((mode >> 12) & 017).suffixp_f(mode));
}

char			*ft_stpcpy(char *dst, char *src)
{
	while (*src)
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
	return (dst);
}

int				ft_inodesize(t_env *env, t_file *file)
{
	ino_t		inode;
	int			size;

	(void)env;
	inode = file->stat.st_ino;
	size = 1;
	while (inode > 9)
	{
		size++;
		inode /= 10;
	}
	return (size);
}

void			ft_inodeprint(t_env *env, t_file *file, int spaces)
{
	ino_t		inode;
	ino_t		power;

	while (spaces--)
		ft_fillbuff_c(env, 1, ' ');
	inode = file->stat.st_ino;
	power = 1;
	while (inode / 10 >= power)
		power *= 10;
	while (power)
	{
		ft_fillbuff_c(env, 1, inode / power % 10 + '0');
		power /= 10;
	}
	ft_fillbuff_c(env, 1, ' ');
}

int				ft_blockssize(t_env *env, t_file *file)
{
	blkcnt_t	blocks;
	int			size;
	
	blocks = (file->stat.st_blocks * 512 + (env->blocksize - 1))
		/ env->blocksize;
	size = 1;
	while (blocks > 9)
	{
		size++;
		blocks /= 10;
	}
	return (size);
}

void			ft_blocksprint(t_env *env, t_file *file, int spaces)
{
	blkcnt_t	blocks;
	blkcnt_t	power;

	while (spaces--)
		ft_fillbuff_c(env, 1, ' ');
	blocks = (file->stat.st_blocks * 512 + (env->blocksize - 1))
		/ env->blocksize;
	power = 1;
	while (blocks / 10 >= power)
		power *= 10;
	while (power)
	{
		ft_fillbuff_c(env, 1, blocks / power % 10 + '0');
		power /= 10;
	}
	ft_fillbuff_c(env, 1, ' ');
}

void			ft_typeprint(t_env *env, t_file *file, int spaces)
{
	(void)spaces;
	ft_fillbuff_c(env, 1, ft_ftypetab((file->stat.st_mode >> 12) & 017).lprint);
}

void			ft_permsprint(t_env *env, t_file *file, int spaces)
{
	int			i;

	(void)spaces;
	i = 0;
	while (i < 9)
	{
		ft_fillbuff_c(env, 1, ft_getperm(i, file->stat.st_mode));
		i++;
	}
}

void			ft_eaaclprint(t_env *env, t_file *file, int spaces)
{
	char		ea;
	acl_t		acl;

	(void)spaces;
	if (listxattr(file->path, &ea, 1, 0) > 0)
		ft_fillbuff_c(env, 1, '@');
	else if ((acl = acl_get_file(file->path, ACL_TYPE_ACCESS)))
	{
		ft_fillbuff_c(env, 1, '+');
		acl_free(acl);
	}
	else
		ft_fillbuff_c(env, 1, ' ');
	ft_fillbuff_c(env, 1, ' ');
}

int				ft_nlinksize(t_env *env, t_file *file)
{
	nlink_t		nlink;
	int			size;

	(void)env;
	nlink = file->stat.st_nlink;
	size = 1;
	while (nlink > 9)
	{
		size++;
		nlink /= 10;
	}
	return (size);
}

void			ft_nlinkprint(t_env *env, t_file *file, int spaces)
{
	nlink_t		nlink;
	nlink_t		power;

	while (spaces--)
		ft_fillbuff_c(env, 1, ' ');
	nlink = file->stat.st_nlink;
	power = 1;
	while (nlink / 10 >= power)
		power *= 10;
	while (power)
	{
		ft_fillbuff_c(env, 1, nlink / power % 10 + '0');
		power /= 10;
	}
	ft_fillbuff_c(env, 1, ' ');
}

int				ft_uididsize(t_env *env, t_file *file)
{
	uid_t		uid;
	int			size;

	(void)env;
	uid = file->stat.st_uid;
	size = 1;
	while (uid > 9)
	{
		size++;
		uid /= 10;
	}
	return (size);
}

int				ft_uidnamesize(t_env *env, t_file *file)
{
	int			size;

	(void)env;
	if (!(file->uid = getpwuid(file->stat.st_uid)))
		return (ft_uididsize(env, file));
	size = 0;
	while (file->uid->pw_name[size])
		size++;
	return (size);
}

int				ft_uidsize(t_env *env, t_file *file)
{
	return (env->uidsize_f(env, file));
}

void			ft_uididprint(t_env *env, t_file *file)
{
	uid_t		uid;
	uid_t		power;

	uid = file->stat.st_uid;
	power = 1;
	while (uid / 10 >= power)
		power *= 10;
	while (power)
	{
		ft_fillbuff_c(env, 1, uid / power % 10 + '0');
		power /= 10;
	}
}

void			ft_uidnameprint(t_env *env, t_file *file)
{
	if (file->uid)
		ft_fillbuff(env, 1, file->uid->pw_name);
	else
		ft_uididprint(env, file);
}

void			ft_uidprint(t_env *env, t_file *file, int spaces)
{
	env->uidprint_f(env, file);
	while (spaces--)
		ft_fillbuff_c(env, 1, ' ');
}

int				ft_gididsize(t_env *env, t_file *file)
{
	gid_t		gid;
	int			size;

	(void)env;
	gid = file->stat.st_gid;
	size = 1;
	while (gid > 9)
	{
		size++;
		gid /= 10;
	}
	return (size);
}

int				ft_gidnamesize(t_env *env, t_file *file)
{
	int			size;

	(void)env;
	if (!(file->gid = getgrgid(file->stat.st_gid)))
		return (ft_gididsize(env, file));
	size = 0;
	while (file->gid->gr_name[size])
		size++;
	return (size);
}

int				ft_gidsize(t_env *env, t_file *file)
{
	return (env->gidsize_f(env, file));
}

void			ft_gididprint(t_env *env, t_file *file)
{
	gid_t		gid;
	gid_t		power;

	gid = file->stat.st_gid;
	power = 1;
	while (gid / 10 >= power)
		power *= 10;
	while (power)
	{
		ft_fillbuff_c(env, 1, gid / power % 10 + '0');
		power /= 10;
	}
}

void			ft_gidnameprint(t_env *env, t_file *file)
{
	if (file->gid)
		ft_fillbuff(env, 1, file->gid->gr_name);
	else
		ft_gididprint(env, file);
}

void			ft_gidprint(t_env *env, t_file *file, int spaces)
{
	env->gidprint_f(env, file);
	while (spaces--)
		ft_fillbuff_c(env, 1, ' ');
}

int				ft_sizebytesize(t_env *env, t_file *file)
{
	off_t		off;
	int			size;

	(void)env;
	off = file->stat.st_size;
	size = 1;
	while (off > 9)
	{
		size++;
		off /= 10;
	}
	return (size);
}

int				ft_sizeunitsize(t_env *env, t_file *file)
{
	(void)env;
	(void)file;
	return (5);
}

int				ft_sizesize(t_env *env, t_file *file)
{
	if (S_ISCHR(file->stat.st_mode) || S_ISBLK(file->stat.st_mode))
		return (8);
	return (env->sizesize_f(env, file));
}

void			ft_majprint(t_env *env, t_file *file)
{
	dev_t		maj;
	dev_t		power;

	maj = major(file->stat.st_rdev);
	power = 1;
	while (maj / 10 >= power)
		power *= 10;
	if (power < 100)
		ft_fillbuff_c(env, 1, ' ');
	if (power < 10)
		ft_fillbuff_c(env, 1, ' ');
	while (power)
	{
		ft_fillbuff_c(env, 1, maj / power % 10 + '0');
		power /= 10;
	}
}

void			ft_minprint(t_env *env, t_file *file)
{
	dev_t		min;
	dev_t		power;

	min = minor(file->stat.st_rdev);
	power = 1;
	while (min / 10 >= power)
		power *= 10;
	if (power < 100)
		ft_fillbuff_c(env, 1, ' ');
	if (power < 10)
		ft_fillbuff_c(env, 1, ' ');
	while (power)
	{
		ft_fillbuff_c(env, 1, min / power % 10 + '0');
		power /= 10;
	}
}

void			ft_majminprint(t_env *env, t_file *file, int spaces)
{
	while (spaces--)
		ft_fillbuff_c(env, 1, '0');
	ft_majprint(env, file);
	ft_fillbuff(env, 1, ", ");
	ft_minprint(env, file);
}

void			ft_sizebyteprint(t_env *env, t_file *file, int spaces)
{
	off_t		off;
	off_t		power;

	off = file->stat.st_size;
	power = 1;
	while (spaces--)
		ft_fillbuff_c(env, 1, ' ');
	while (off / 10 >= power)
		power *= 10;
	while (power)
	{
		ft_fillbuff_c(env, 1, off / power % 10 + '0');
		power /= 10;
	}
}

void			ft_sizepunitprint(t_env *env, t_file *file)
{
	off_t		p;
	off_t		t;

	t = TBYTES(file->stat.st_size) % 1024 * 1000 / 1024;
	p = PBYTES(file->stat.st_size) + (t > 949);
	t = ((t + 50) / 100 > 9) ? 0 : (t + 50) / 100;
	if (p > 9)
	{
		ft_fillbuff_c(env, 1, (p > 99) ? p / 100 + '0' : ' ');
		ft_fillbuff_c(env, 1, p / 10 % 10 + '0');
		ft_fillbuff_c(env, 1, p % 10 + '0');
		ft_fillbuff_c(env, 1, 'P');
	}
	else
	{
		ft_fillbuff_c(env, 1, p + '0');
		ft_fillbuff_c(env, 1, '.');
		ft_fillbuff_c(env, 1, t + '0');
		ft_fillbuff_c(env, 1, 'P');
	}
}

void			ft_sizetunitprint(t_env *env, t_file *file)
{
	off_t		t;
	off_t		g;

	g = GBYTES(file->stat.st_size) % 1024 * 1000 / 1024;
	t = TBYTES(file->stat.st_size) + (g > 949);
	g = ((g + 50) / 100 > 9) ? 0 : (g + 50) / 100;
	if (t > 999)
		ft_sizepunitprint(env, file);
	else if (t > 9)
	{
		ft_fillbuff_c(env, 1, (t > 99) ? t / 100 + '0' : ' ');
		ft_fillbuff_c(env, 1, t / 10 % 10 + '0');
		ft_fillbuff_c(env, 1, t % 10 + '0');
		ft_fillbuff_c(env, 1, 'T');
	}
	else
	{
		ft_fillbuff_c(env, 1, t + '0');
		ft_fillbuff_c(env, 1, '.');
		ft_fillbuff_c(env, 1, g + '0');
		ft_fillbuff_c(env, 1, 'T');
	}
}

void			ft_sizegunitprint(t_env *env, t_file *file)
{
	off_t		g;
	off_t		m;

	m = MBYTES(file->stat.st_size) % 1024 * 1000 / 1024;
	g = GBYTES(file->stat.st_size) + (m > 949);
	m = ((m + 50) / 100 > 9) ? 0 : (m + 50) / 100;
	if (g > 999)
		ft_sizetunitprint(env, file);
	else if (g > 9)
	{
		ft_fillbuff_c(env, 1, (g > 99) ? g / 100 + '0' : ' ');
		ft_fillbuff_c(env, 1, g / 10 % 10 + '0');
		ft_fillbuff_c(env, 1, g % 10 + '0');
		ft_fillbuff_c(env, 1, 'G');
	}
	else
	{
		ft_fillbuff_c(env, 1, g + '0');
		ft_fillbuff_c(env, 1, '.');
		ft_fillbuff_c(env, 1, m + '0');
		ft_fillbuff_c(env, 1, 'G');
	}
}

void			ft_sizemunitprint(t_env *env, t_file *file)
{
	off_t		m;
	off_t		k;

	k = KBYTES(file->stat.st_size) % 1024 * 1000 / 1024;
	m = MBYTES(file->stat.st_size) + (k > 949);
	k = ((k + 50) / 100 > 9) ? 0 : (k + 50) / 100;
	if (m > 999)
		ft_sizegunitprint(env, file);
	else if (m > 9)
	{
		ft_fillbuff_c(env, 1, (m > 99) ? m / 100 + '0' : ' ');
		ft_fillbuff_c(env, 1, m / 10 % 10 + '0');
		ft_fillbuff_c(env, 1, m % 10 + '0');
		ft_fillbuff_c(env, 1, 'M');
	}
	else
	{
		ft_fillbuff_c(env, 1, m + '0');
		ft_fillbuff_c(env, 1, '.');
		ft_fillbuff_c(env, 1, k + '0');
		ft_fillbuff_c(env, 1, 'M');
	}
}

void			ft_sizekunitprint(t_env *env, t_file *file)
{
	off_t		k;
	off_t		b;

	b = file->stat.st_size % 1024 * 1000 / 1024;
	k = KBYTES(file->stat.st_size) + (b > 949);
	b = ((b + 50) / 100 > 9) ? 0 : (b + 50) / 100;
	if (k > 999)
		ft_sizemunitprint(env, file);
	else if (k > 9)
	{
		ft_fillbuff_c(env, 1, (k > 99) ? k / 100 + '0' : ' ');
		ft_fillbuff_c(env, 1, k / 10 % 10 + '0');
		ft_fillbuff_c(env, 1, k % 10 + '0');
		ft_fillbuff_c(env, 1, 'K');
	}
	else
	{
		ft_fillbuff_c(env, 1, k + '0');
		ft_fillbuff_c(env, 1, '.');
		ft_fillbuff_c(env, 1, b + '0');
		ft_fillbuff_c(env, 1, 'K');
	}
}

void			ft_sizebunitprint(t_env *env, t_file *file)
{
	off_t		b;

	b = file->stat.st_size;
	if (b > 999)
		ft_sizekunitprint(env, file);
	else
	{
		ft_fillbuff_c(env, 1, (b > 99) ? b / 100 + '0' : ' ');
		ft_fillbuff_c(env, 1, (b > 9) ? b / 10 % 10 + '0' : ' ');
		ft_fillbuff_c(env, 1, b % 10 + '0');
		ft_fillbuff_c(env, 1, 'B');
	}
}

void			ft_sizeunitprint(t_env *env, t_file *file, int spaces)
{
	while (spaces--)
		ft_fillbuff_c(env, 1, ' ');
	ft_fillbuff_c(env, 1, ' ');
	ft_sizebunitprint(env, file);
}

void			ft_sizeprint(t_env *env, t_file *file, int spaces)
{
	if (S_ISCHR(file->stat.st_mode) || S_ISBLK(file->stat.st_mode))
		return (ft_majminprint(env, file, spaces));
	return (env->sizeprint_f(env, file, spaces));
}

void			ft_colorprint(t_env *env, t_file *file, int spaces)
{
	(void)spaces;
	ft_fillbuff(env, 1, ft_ftypetab((file->stat.st_mode >> 12) & 017).
		color_f(env, file->stat.st_mode)[0]);
	ft_fillbuff(env, 1, ft_ftypetab((file->stat.st_mode >> 12) & 017).
		color_f(env, file->stat.st_mode)[1]);
}

void			ft_nameprint(t_env *env, t_file *file, int spaces)
{
	(void)spaces;
	ft_fillbuff(env, 1, file->name);
}

void			ft_endcolorprint(t_env *env, t_file *file, int spaces)
{
	(void)spaces;
	ft_fillbuff(env, 1, ft_ftypetab((file->stat.st_mode >> 12) & 017).
		color_f(env, file->stat.st_mode)[2]);
}

void			ft_suffixprint(t_env *env, t_file *file, int spaces)
{
	(void)spaces;
	ft_fillbuff(env, 1, env->getsuffix_f(file->stat.st_mode));
}

t_data				ft_normaldatatab(int i)
{
	static t_data	normaldatatab[] = {
		{&ft_inodesize, &ft_inodeprint},
		{&ft_blockssize, &ft_blocksprint},
		{NULL, &ft_colorprint},
		{NULL, &ft_nameprint},
		{NULL, &ft_endcolorprint},
		{NULL, &ft_suffixprint}
	};

	return (normaldatatab[i]);
}

t_data				ft_longdatatab(int i)
{
	static t_data	longdatatab[] = {
		{&ft_inodesize, &ft_inodeprint},
		{&ft_blockssize, &ft_blocksprint},
		{NULL, &ft_typeprint},
		{NULL, &ft_permsprint},
		{NULL, &ft_eaaclprint},
		{&ft_nlinksize, &ft_nlinkprint},
		{&ft_uidsize, &ft_uidprint},
		{&ft_gidsize, &ft_gidprint},
		{NULL, NULL},
		{&ft_sizesize, &ft_sizeprint},
//		{NULL, &ft_timeprint},
		{NULL, &ft_colorprint},
		{NULL, &ft_nameprint},
		{NULL, &ft_endcolorprint},
		{NULL, &ft_suffixprint},
//		{NULL, &ft_linkprint}
	};

	return (longdatatab[i]);
}

int				ft_addarg(t_file **list, char *arg, char *path, t_file *file)
{
	if (!(file->name = arg) ||
		!(file->path = path))
		return (1);
	file->next = *list;
	*list = file;
	return (0);
}

int				ft_nohidden_select(const char *file_name)
{
	return (file_name[0] != '.');
}

int				ft_select_all(const char *file_name)
{
	(void)file_name;
	return (1);
}

int				ft_nodot_select(const char *file_name)
{
	return (ft_strcmp(file_name, ".") && ft_strcmp(file_name, ".."));
}

int				ft_atoi(char *str)
{
	int			result;
	int			sign;

	result = 0;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0') * sign;
		str++;
	}
	return (result);
}

void			ft_config_blocksize(t_env *env)
{
	char		*envblksize;

	if (!(envblksize = getenv("BLOCKSIZE")))
		env->blocksize = DEF_BLOCKSIZE;
	else
		env->blocksize = ft_atoi(envblksize);
	if (env->blocksize < 512)
	{
		env->blocksize = 512;
		ft_fillbuff(env, 2, env->prog_name);
		ft_fillbuff(env, 2, ": minimum blocksize is 512\n");
	}
	else if (env->blocksize > 1073741824)
	{
		env->blocksize = 1073741824;
		ft_fillbuff(env, 2, env->prog_name);
		ft_fillbuff(env, 2, ": maximum blocksize is 1G\n");
	}
	else
		env->blocksize = env->blocksize / 512 * 512;
}

void			ft_config(t_env *env)
{
	env->size = 0;
	env->readarg_f = &ft_defreadarg;
	env->sort_f = &ft_merge_sort;
	env->cmp_f = &ft_ascii_cmp;
	env->print_f = &ft_print_oebl;
	env->explore_f = &ft_explore;
	env->select_f = &ft_nohidden_select;
	env->gettime_f = &ft_getmtime;
	env->getsuffix_f = NULL;
	env->total = 0;
	env->normal_mask = n_def_mask;
	env->long_mask = l_def_mask;
	env->blocksize = 0;
	env->colortab = NULL;
	env->badargs = NULL;
	env->fileargs = NULL;
	env->dirargs = NULL;
}

time_t			ft_getbirthtime(struct stat *stat)
{
	return (stat->st_birthtime);
}

time_t			ft_getatime(struct stat *stat)
{
	return (stat->st_atime);
}

time_t			ft_getmtime(struct stat *stat)
{
	return (stat->st_mtime);
}

time_t			ft_getctime(struct stat *stat)
{
	return (stat->st_ctime);
}

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

void			ft_freelist(t_file *list)
{
	if (!list)
		return ;
	ft_freelist(list->next);
	free(list->name);
	free(list->path);
	free(list);
}

void			ft_badargs(t_env *env)
{
	t_file		*list;

	env->badargs = ft_rev_list(env, env->badargs, &ft_ascii_cmp);
	list = env->badargs;
	while (list)
	{
		ft_fillbuff(env, 2, env->prog_name);
		ft_fillbuff(env, 2, ": ");
		ft_fillbuff(env, 2, list->name);
		ft_fillbuff(env, 2, ": ");
		ft_fillbuff(env, 2, list->path);
		ft_fillbuff(env, 2, "\n");
		list = list->next;
	}
	ft_freelist(env->badargs);
	env->badargs = NULL;
}

int				ft_getmax(t_env *env, t_file *list, int i)
{
	int			max;

	max = 0;
	while (list)
	{
		if ((list->size[i] = ft_normaldatatab(i).size(env, list)) > max)
			max = list->size[i];
		list = list->next;
	}
	return (max);
}

void			ft_normalsize(t_env *env, t_file *list, int *size)
{
	int			i;

	i = 0;
	while (env->normal_mask >> i)
	{
		if ((env->normal_mask >> i) & 1 && ft_normaldatatab(i).size)
			size[i] = ft_getmax(env, list, i);
		i++;
	}
}

void			ft_normalprint(t_env *env, t_file *file, int *size)
{
	int			i;

	i = 0;
	while (env->normal_mask >> i)
	{
		if ((env->normal_mask >> i) & 1)
			ft_normaldatatab(i).print(env, file, size[i] - file->size[i]);
		i++;
	}
}

void			ft_totalprint(t_env *env, t_file *list)
{
	blkcnt_t	total;
	blkcnt_t	power;

	total = 0;
	while (list)
	{
		total = total + list->stat.st_blocks;
		list = list->next;
	}
	total = (total * 512 + (env->blocksize - 1)) / env->blocksize;
	ft_fillbuff(env, 1, "total ");
	power = 1;
	while (total / 10 >= power)
		power *= 10;
	while (power)
	{
		ft_fillbuff_c(env, 1, total / power % 10 + '0');
		power /= 10;
	}
	ft_fillbuff_c(env, 1, '\n');
}

void			ft_print_oebl(t_env *env)
{
	t_file		*list;
	int			size[6];

	list = env->fileargs;
	ft_normalsize(env, list, size);
	if (env->total & 1)
		ft_totalprint(env, list);
	while (list)
	{
		ft_normalprint(env, list, size);
		ft_fillbuff_c(env, 1, '\n');
		list = list->next;
	}
}

void			ft_print_comma(t_env *env)
{
	t_file		*list;

	list = env->fileargs;
	while (list)
	{
		ft_fillbuff(env, 1, list->name);
		if (list->next)
			ft_fillbuff(env, 1, ", ");
		else
			ft_fillbuff_c(env, 1, '\n');
		list = list->next;
	}
}

/*void			ft_print_long(t_env *env)
{
	t_file		*list;
	t_szdt		max;
	int			i;

}*/

void			ft_fileargs(t_env *env)
{
	env->fileargs = env->sort_f(env, env->fileargs, env->cmp_f);
	env->print_f(env);
	ft_freelist(env->fileargs);
	env->fileargs = NULL;
	if (env->dirargs)
		ft_fillbuff_c(env, 1, '\n');
}

char			*ft_getpath(char *dir_path, char *name)
{
	char		*path;
	char		*tmp;

	if (!(path = (char *)malloc(ft_strlen(dir_path) + ft_strlen(name) + 2)))
		return (NULL);
	tmp = ft_stpcpy(path, dir_path);
	if (path != tmp && tmp[-1] != '/')
	{
		*tmp = '/';
		tmp++;
	}
	ft_stpcpy(tmp, name);
	return (path);
}

void			ft_direrror(t_env *env)
{
	char		*error;

	error = strerror(errno);
	ft_fillbuff(env, 2, env->prog_name);
	ft_fillbuff(env, 2, ": ");
	ft_fillbuff(env, 2, env->dirargs->name);
	ft_fillbuff(env, 2, ": ");
	ft_fillbuff(env, 2, error);
	ft_fillbuff_c(env, 2, '\n');
}

int				ft_getdir(t_env *env)
{
	DIR			*dir_ptr;
	t_dirent	*file_ptr;
	t_file		*file;

	if (!(dir_ptr = opendir(env->dirargs->path)))
	{
		ft_direrror(env);
		return (0);
	}
	while ((file_ptr = readdir(dir_ptr)))
	{
		if (env->select_f(file_ptr->d_name))
		{
			if (!(file = (t_file *)malloc(sizeof(t_file))) ||
				ft_addarg(&(env->fileargs), ft_strdup(file_ptr->d_name),
				ft_getpath(env->dirargs->path, file_ptr->d_name), file))
				return (1);
			lstat(file->path, &(file->stat));
		}
	}
	closedir(dir_ptr);
	return (0);
}

int				ft_explore(t_env *env)
{
	t_file		*tmp;

	env->dirargs = env->sort_f(env, env->dirargs, env->cmp_f);
	while (env->dirargs)
	{
		env->dirtitle_f(env);
		if (ft_getdir(env))
			return (1);
		if (env->fileargs)
			env->fileargs = env->sort_f(env, env->fileargs, env->cmp_f);
		env->print_f(env);
		ft_freelist(env->fileargs);
		env->fileargs = NULL;
		tmp = env->dirargs;
		env->dirargs = env->dirargs->next;
		free(tmp->name);
		free(tmp->path);
		free(tmp);
		if (env->dirargs)
			ft_fillbuff_c(env, 1, '\n');
	}
	return (0);
}

void			ft_addorfree(t_env *env, t_file *list)
{
	if (list->next)
		ft_addorfree(env, list->next);
	if (list->stat.st_mode & S_IFDIR && ft_strcmp(list->name, ".") &&
		ft_strcmp(list->name, ".."))
	{
		list->next = env->dirargs;
		env->dirargs = list;
	}
	else
	{
		free(list->name);
		free(list->path);
		free(list);
	}
}

int				ft_recursive_explore(t_env *env)
{
	t_file		*tmp;

	env->dirargs = env->sort_f(env, env->dirargs, env->cmp_f);
	while (env->dirargs)
	{
		env->dirtitle_f(env);
		if (ft_getdir(env))
			return (1);
		if (env->fileargs)
			env->fileargs = env->sort_f(env, env->fileargs, env->cmp_f);
		env->print_f(env);
		tmp = env->dirargs;
		env->dirargs = env->dirargs->next;
		free(tmp->name);
		free(tmp->path);
		free(tmp);
		if (env->fileargs)
			ft_addorfree(env, env->fileargs);
		env->fileargs = NULL;
		if (env->dirargs)
			ft_fillbuff_c(env, 1, '\n');
	}
	return (0);
}

void			ft_titleddir(t_env *env)
{
	ft_fillbuff(env, 1, env->dirargs->path);
	ft_fillbuff(env, 1, ":\n");
}

void			ft_untitleddir(t_env *env)
{
	env->dirtitle_f = &ft_titleddir;
}

void			ft_freecolortab(t_env *env)
{
	int			i;

	i = 0;
	while (i < 12)
	{
		free(env->colortab[i]);
		i++;
	}
	free(env->colortab);
	env->colortab = NULL;
}

int				ft_ls(t_env *env)
{
	ft_config(env);
	if (ft_readargv(env))
		return (1);
	env->dirtitle_f = (env->argc > 1) ? &ft_titleddir : &ft_untitleddir;
	if (env->badargs)
		ft_badargs(env);
	if (env->fileargs)
		ft_fileargs(env);
	env->total = env->total >> 1;
	if (env->dirargs && env->explore_f(env))
		return (1);
	ft_writebuff(env);
	if (env->colortab)
		ft_freecolortab(env);
	return (0);
}

int				main(int argc, char **argv)
{
	t_env		env;

	env.argc = argc;
	env.prog_name = argv[0];
	env.argv = argv;
	if (ft_ls(&env))
		return (1);
	return (0);
}
