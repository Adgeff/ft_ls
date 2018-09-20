/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 07:34:55 by geargenc          #+#    #+#             */
/*   Updated: 2018/09/20 15:38:47 by geargenc         ###   ########.fr       */
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
	size = 2;
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
	size = 2;
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
	acl_t		acl;

	(void)spaces;
	if (listxattr(file->path, NULL, 0, 0) > 0)
		ft_fillbuff_c(env, 1, '@');
	else if ((acl = acl_get_link_np(file->path, ACL_TYPE_EXTENDED)))
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

int					ft_uidnamesize(t_env *env, t_file *file)
{
	struct passwd	*uid;
	int				size;

	(void)env;
	if (!(uid = getpwuid(file->stat.st_uid)))
		return (ft_uididsize(env, file));
	size = 0;
	while (uid->pw_name[size])
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

void				ft_uidnameprint(t_env *env, t_file *file)
{
	struct passwd	*uid;

	if ((uid = getpwuid(file->stat.st_uid)))
		ft_fillbuff(env, 1, uid->pw_name);
	else
		ft_uididprint(env, file);
}

void			ft_uidprint(t_env *env, t_file *file, int spaces)
{
	env->uidprint_f(env, file);
	while (spaces--)
		ft_fillbuff_c(env, 1, ' ');
	ft_fillbuff(env, 1, "  ");
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

int					ft_gidnamesize(t_env *env, t_file *file)
{
	struct group	*gid;
	int				size;

	(void)env;
	if (!(gid = getgrgid(file->stat.st_gid)))
		return (ft_gididsize(env, file));
	size = 0;
	while (gid->gr_name[size])
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

void				ft_gidnameprint(t_env *env, t_file *file)
{
	struct group	*gid;

	if ((gid = getgrgid(file->stat.st_gid)))
		ft_fillbuff(env, 1, gid->gr_name);
	else
		ft_gididprint(env, file);
}

void			ft_gidprint(t_env *env, t_file *file, int spaces)
{
	env->gidprint_f(env, file);
	while (spaces--)
		ft_fillbuff_c(env, 1, ' ');
	ft_fillbuff(env, 1, "  ");
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

void			ft_majminprint(t_env *env, t_file *file)
{
	ft_majprint(env, file);
	ft_fillbuff(env, 1, ", ");
	ft_minprint(env, file);
}

void			ft_sizebyteprint(t_env *env, t_file *file)
{
	off_t		off;
	off_t		power;

	off = file->stat.st_size;
	power = 1;
	while (off / 10 >= power)
		power *= 10;
	while (power)
	{
		ft_fillbuff_c(env, 1, off / power % 10 + '0');
		power /= 10;
	}
}

void			ft_sizemoreunitprint(t_env *env, off_t size, char *units)
{
	off_t		u;
	off_t		d;

	d = size % 1024 * 1000 / 1024;
	u = size / 1024;
	u = u + (u > 9 ? d > 499 : d > 949);
	d = (d + 50) / 100 % 10;
	if (u > 999)
		ft_sizemoreunitprint(env, size / 1024, units + 1);
	else if (u > 9)
	{
		ft_fillbuff_c(env, 1, (u > 99) ? u / 100 + '0' : ' ');
		ft_fillbuff_c(env, 1, u / 10 % 10 + '0');
		ft_fillbuff_c(env, 1, u % 10 + '0');
		ft_fillbuff_c(env, 1, *units);
	}
	else
	{
		ft_fillbuff_c(env, 1, u + '0');
		ft_fillbuff_c(env, 1, '.');
		ft_fillbuff_c(env, 1, d + '0');
		ft_fillbuff_c(env, 1, *units);
	}
}

void			ft_sizeunitprint(t_env *env, t_file *file)
{
	off_t		u;

	ft_fillbuff_c(env, 1, ' ');
	u = file->stat.st_size;
	if (u > 999)
		ft_sizemoreunitprint(env, u, "KMGTP");
	else
	{
		ft_fillbuff_c(env, 1, (u > 99) ? u / 100 + '0' : ' ');
		ft_fillbuff_c(env, 1, (u > 9) ? u / 10 % 10 + '0' : ' ');
		ft_fillbuff_c(env, 1, u % 10 + '0');
		ft_fillbuff_c(env, 1, 'B');
	}
}

void			ft_sizeprint(t_env *env, t_file *file, int spaces)
{
	while (spaces--)
		ft_fillbuff_c(env, 1, ' ');
	if (S_ISCHR(file->stat.st_mode) || S_ISBLK(file->stat.st_mode))
		ft_majminprint(env, file);
	else
		env->sizeprint_f(env, file);
	ft_fillbuff_c(env, 1, ' ');
}

void			ft_daymonthprint(t_env *env, struct tm *fstm)
{
	if (*nl_langinfo(D_MD_ORDER) == 'd')
	{
		ft_fillbuff_c(env, 1, (fstm->tm_mday / 10) ?
			fstm->tm_mday / 10 + '0' : ' ');
		ft_fillbuff_c(env, 1, fstm->tm_mday % 10 + '0');
		ft_fillbuff_c(env, 1, ' ');
		ft_fillbuff(env, 1, nl_langinfo(ABMON_1 + fstm->tm_mon));
	}
	else
	{
		ft_fillbuff(env, 1, nl_langinfo(ABMON_1 + fstm->tm_mon));
		ft_fillbuff_c(env, 1, ' ');
		ft_fillbuff_c(env, 1, (fstm->tm_mday / 10) ?
			fstm->tm_mday / 10 + '0' : ' ');
		ft_fillbuff_c(env, 1, fstm->tm_mday % 10 + '0');
	}
}

void			ft_hmsprint(t_env *env, int hms)
{
	ft_fillbuff_c(env, 1, hms / 10 + '0');
	ft_fillbuff_c(env, 1, hms % 10 + '0');
}

void			ft_yearprint(t_env *env, int year)
{
	ft_fillbuff_c(env, 1, year / 1000 % 10 + '0');
	ft_fillbuff_c(env, 1, year / 100 % 10 + '0');
	ft_fillbuff_c(env, 1, year / 10 % 10 + '0');
	ft_fillbuff_c(env, 1, year % 10 + '0');
}

void			ft_shorttimeprint(t_env *env, t_file *file)
{
	time_t		ftime;
	struct tm	*fstm;

	ftime = env->gettime_f(&(file->stat));
	fstm = localtime(&ftime);
	ft_daymonthprint(env, fstm);
	ft_fillbuff_c(env, 1, ' ');
	if (ftime + SIXMONTHS > env->now && ftime < env->now + SIXMONTHS)
	{
		ft_hmsprint(env, fstm->tm_hour);
		ft_fillbuff_c(env, 1, ':');
		ft_hmsprint(env, fstm->tm_min);
	}
	else
	{
		ft_fillbuff_c(env, 1, ' ');
		ft_yearprint(env, fstm->tm_year + 1900);
	}
	ft_fillbuff_c(env, 1, ' ');
}

void			ft_longtimeprint(t_env *env, t_file *file)
{
	time_t		ftime;
	struct tm	*fstm;

	ftime = env->gettime_f(&(file->stat));
	fstm = localtime(&ftime);
	ft_daymonthprint(env, fstm);
	ft_fillbuff_c(env, 1, ' ');
	ft_hmsprint(env, fstm->tm_hour);
	ft_fillbuff_c(env, 1, ':');
	ft_hmsprint(env, fstm->tm_min);
	ft_fillbuff_c(env, 1, ':');
	ft_hmsprint(env, fstm->tm_sec);
	ft_fillbuff_c(env, 1, ' ');
	ft_yearprint(env, fstm->tm_year + 1900);
	ft_fillbuff_c(env, 1, ' ');
}

void			ft_timeprint(t_env *env, t_file *file, int spaces)
{
	(void)spaces;
	env->timeprint_f(env, file);
}

void			ft_colorprint(t_env *env, t_file *file, int spaces)
{
	(void)spaces;
	ft_fillbuff(env, 1, ft_ftypetab((file->stat.st_mode >> 12) & 017).
		color_f(env, file->stat.st_mode)[0]);
	ft_fillbuff(env, 1, ft_ftypetab((file->stat.st_mode >> 12) & 017).
		color_f(env, file->stat.st_mode)[1]);
}

int				ft_namesize(t_env *env, t_file *file)
{
	char		*name;
	int			i;

	(void)env;
	name = file->name;
	i = 0;
	while (name[i])
		i++;
	return (i);
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

int				ft_suffixsize(t_env *env, t_file *file)
{
	if (*env->getsuffix_f(file->stat.st_mode))
		return (1);
	else
		return (0);
}

void			ft_suffixprint(t_env *env, t_file *file, int spaces)
{
	(void)spaces;
	ft_fillbuff(env, 1, env->getsuffix_f(file->stat.st_mode));
}

void			ft_linkprint(t_env *env, t_file *file, int spaces)
{
	char		buf[1023];

	(void)spaces;
	if (S_ISLNK(file->stat.st_mode))
	{
		ft_fillbuff(env, 1, " -> ");
		buf[readlink(file->path, buf, sizeof(buf))] = '\0';
		ft_fillbuff(env, 1, buf);
	}
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

t_data				ft_coldatatab(int i)
{
	static t_data	normaldatatab[] = {
		{&ft_inodesize, &ft_inodeprint},
		{&ft_blockssize, &ft_blocksprint},
		{NULL, &ft_colorprint},
		{&ft_namesize, &ft_nameprint},
		{NULL, &ft_endcolorprint},
		{&ft_suffixsize, &ft_suffixprint}
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
		{NULL, &ft_timeprint},
		{NULL, &ft_colorprint},
		{NULL, &ft_nameprint},
		{NULL, &ft_endcolorprint},
		{NULL, &ft_suffixprint},
		{NULL, &ft_linkprint}
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

void				ft_config_functions(t_env *env)
{
	env->readarg_f = &ft_defreadarg;
	env->sort_f = &ft_merge_sort;
	env->cmp_f = &ft_ascii_cmp;
	env->print_f = &ft_print_oebl;
	env->explore_f = &ft_explore;
	env->select_f = &ft_nohidden_select;
	env->gettime_f = &ft_getmtime;
	env->getsuffix_f = NULL;
	env->uidsize_f = &ft_uidnamesize;
	env->uidprint_f = &ft_uidnameprint;
	env->gidsize_f = &ft_gidnamesize;
	env->gidprint_f = &ft_gidnameprint;
	env->sizesize_f = &ft_sizebytesize;
	env->sizeprint_f = &ft_sizebyteprint;
	env->timeprint_f = &ft_shorttimeprint;
}

void				ft_config_term(t_env *env)
{
	struct winsize	win;

	ioctl(1, TIOCGWINSZ, &win);
	env->ws_col = win.ws_col;
	env->print_f = &ft_print_colvert;
}

void				ft_config(t_env *env)
{
	ft_config_functions(env);
	env->ws_col = 80;
	env->size = 0;
	env->total = 0;
	env->normal_mask = n_def_mask;
	env->long_mask = l_def_mask;
	env->blocksize = 0;
	env->colortab = NULL;
	env->badargs = NULL;
	env->fileargs = NULL;
	env->dirargs = NULL;
	if (isatty(1))
		ft_config_term(env);
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

int				ft_getmax(t_env *env, t_file *list, int i,
				int (*f)(t_env *, t_file *))
{
	int			max;

	max = 0;
	while (list)
	{
		if ((list->size[i] = f(env, list)) > max)
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
			size[i] = ft_getmax(env, list, i, ft_normaldatatab(i).size);
		i++;
	}
}

void			ft_longsize(t_env *env, t_file *list, int *size)
{
	int			i;

	i = 0;
	while (env->long_mask >> i)
	{
		if ((env->long_mask >> i) & 1 && ft_longdatatab(i).size)
			size[i] = ft_getmax(env, list, i, ft_longdatatab(i).size);
		i++;
	}
}

void			ft_colsize(t_env *env, t_file *list, int *size)
{
	int			i;

	i = 0;
	while (env->normal_mask >> i)
	{
		if ((env->normal_mask >> i) & 1 && ft_coldatatab(i).size)
			size[i] = ft_getmax(env, list, i, ft_coldatatab(i).size);
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

void			ft_longprint(t_env *env, t_file *file, int *size)
{
	int			i;

	i = 0;
	while (env->long_mask >> i)
	{
		if ((env->long_mask >> i) & 1)
			ft_longdatatab(i).print(env, file, size[i] - file->size[i]);
		i++;
	}
}

void			ft_colprint(t_env *env, t_file *file, int *size)
{
	int			i;

	i = 0;
	while (env->normal_mask >> i)
	{
		if ((env->normal_mask >> i) & 1)
			ft_coldatatab(i).print(env, file, size[i] - file->size[i]);
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
	if (list && env->total & 1)
		ft_totalprint(env, list);
	while (list)
	{
		ft_normalprint(env, list, size);
		ft_fillbuff_c(env, 1, '\n');
		list = list->next;
	}
}

int				ft_getmaxfiledatasize(t_env *env, int *size)
{
	int			maxsize;
	int			i;

	maxsize = 0;
	i = 0;
	while (env->normal_mask >> i)
	{
		if ((env->normal_mask >> i) & 1 && ft_coldatatab(i).size)
			maxsize = maxsize + size[i];
		i++;
	}
	return (maxsize);
}

int				ft_getlistsize(t_file *list)
{
	int			i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void			ft_get_colp(t_env *env, t_file *list, int *size, t_colp *colp)
{
	size[5] = 1;
	colp->listsize = ft_getlistsize(list);
	colp->maxdatasize = ft_getmaxfiledatasize(env, size);
	colp->maxdatasize = (colp->maxdatasize + 8) / 8 * 8;
	colp->maxbyline = env->ws_col / colp->maxdatasize;
	if (colp->maxbyline == 0)
		colp->maxbyline = 1;
	colp->lines = (colp->listsize + colp->maxbyline - 1) / colp->maxbyline;
	colp->total = colp->lines * colp->maxbyline;
}

void			ft_order_colvert(t_file *list, t_colp *colp, t_file **order)
{
	int			i;

	i = 0;
	while (i < colp->total)
	{
		if (list)
		{
			order[i % colp->lines * colp->maxbyline + i / colp->lines] = list;
			list = list->next;
		}
		else
			order[i % colp->lines * colp->maxbyline + i / colp->lines] = NULL;
		i++;
	}
}

void			ft_order_colhor(t_file *list, t_colp *colp, t_file **order)
{
	int			i;

	i = 0;
	while (i < colp->total)
	{
		if (list)
		{
			order[i] = list;
			list = list->next;
		}
		else
			order[i] = NULL;
		i++;
	}
}

int				ft_getfiledatasize(t_env *env, t_file *file, int *size)
{
	int			i;
	int			datasize;

	i = 0;
	datasize = 0;
	while (env->normal_mask >> i)
	{
		if ((env->normal_mask >> i) & 1 && ft_coldatatab(i).size)
			datasize = datasize + size[i];
		i++;
	}
	datasize = datasize - size[3] + file->size[3];
	if (env->normal_mask & n_suffix_mask)
		datasize = datasize - size[5] + file->size[5];
	return (datasize);
}

void			ft_col_print(t_env *env, t_colp *colp,
				t_file **order, int *size)
{
	int			i;
	int			j;
	int			spaces;

	j = 0;
	while (j < colp->lines)
	{
		i = 0;
		while (i < colp->maxbyline && order[j * colp->maxbyline + i])
		{
			ft_colprint(env, order[j * colp->maxbyline + i], size);
			if (i + 1 < colp->maxbyline && order[j * colp->maxbyline + i + 1])
			{
				spaces = colp->maxdatasize - ft_getfiledatasize(env,
					order[j * colp->maxbyline + i], size);
				spaces = (spaces + 7) / 8;
				while (spaces--)
					ft_fillbuff_c(env, 1, '\t');
			}
			i++;
		}
		ft_fillbuff_c(env, 1, '\n');
		j++;
	}
}

void			ft_print_colvert(t_env *env)
{
	t_file		*list;
	int			size[6];
	t_colp		colp;
	t_file		**order;

	list = env->fileargs;
	ft_colsize(env, list, size);
	ft_get_colp(env, list, size, & colp);
	if (!(order = (t_file **)malloc(colp.total * sizeof(t_file *))))
		ft_print_oebl(env);
	else
	{
		ft_order_colvert(list, &colp, order);
		if (list && env->total & 1)
			ft_totalprint(env, list);
		ft_col_print(env, &colp, order, size);
		free(order);
	}
}

void			ft_print_colhor(t_env *env)
{
	t_file		*list;
	int			size[6];
	t_colp		colp;
	t_file		**order;

	list = env->fileargs;
	ft_colsize(env, list, size);
	ft_get_colp(env, list, size, & colp);
	if (!(order = (t_file **)malloc(colp.total * sizeof(t_file *))))
		ft_print_oebl(env);
	else
	{
		ft_order_colhor(list, &colp, order);
		if (list && env->total & 1)
			ft_totalprint(env, list);
		ft_col_print(env, &colp, order, size);
		free(order);
	}
}

void			ft_print_comma(t_env *env)
{
	t_file		*list;
	int			size[6];

	list = env->fileargs;
	ft_normalsize(env, list, size);
	while (list)
	{
		ft_normalprint(env, list, size);
		if (list->next)
			ft_fillbuff(env, 1, ", ");
		else
			ft_fillbuff_c(env, 1, '\n');
		list = list->next;
	}
}

void			ft_print_long(t_env *env)
{
	t_file		*list;
	int			size[16];

	list = env->fileargs;
	ft_longsize(env, list, size);
	if (list && env->total & 1)
		ft_totalprint(env, list);
	while (list)
	{
		ft_longprint(env, list, size);
		ft_fillbuff_c(env, 1, '\n');
		list = list->next;
	}
}

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

void			ft_delfile(t_env *env)
{
	t_file		*file;

	file = env->fileargs;
	env->fileargs = env->fileargs->next;
	free(file->name);
	free(file->path);
	free(file);
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
			if (lstat(file->path, &(file->stat)))
				ft_delfile(env);
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
	if (S_ISDIR(list->stat.st_mode) && ft_strcmp(list->name, ".") &&
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
