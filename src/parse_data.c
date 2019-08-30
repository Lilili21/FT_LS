/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 15:31:19 by gfoote            #+#    #+#             */
/*   Updated: 2019/07/24 15:31:21 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsft.h"

int		parse_name(t_curr *new, char *d_name, char *p, t_fl **fl)
{
	char	*tmp;
	char	*link;
	int		status;

	if (new->type != 'l' || (*fl)->l != 1)
	{
		if (!(new->name = ft_strdup(d_name)))
			return (ft_er3(d_name, p, &new));
		return (0);
	}
	if (!(tmp = ft_strjoin(d_name, " -> ")))
		return (ft_er3(d_name, p, &new));
	if (!(link = (char*)malloc(sizeof(char) * PATH_MAX)))
	{
		free(tmp);
		return (ft_er3(d_name, p, &new));
	}
	if ((status = readlink(p, link, PATH_MAX - 1)) > 0)
		link[status] = '\0';
	new->name = ft_strjoin(tmp, link);
	free(tmp);
	free(link);
	if (!new->name)
		return (ft_er3(d_name, p, &new));
	return (0);
}

int		parse_date(t_curr *new, t_fl **fl, struct stat st)
{
	char		**tmp;
	time_t		now;
	int			*c_time;
	int			*n_time;

	if ((*fl)->t == 1)
		new->compare_date = st.st_mtimespec.tv_sec;
	if ((*fl)->l != 1)
		return (0);
	now = time(0);
	CHECK(tmp = ft_strsplit(ctime(&now), ' '));
	n_time = ft_fill_date(tmp);
	ft_strdl2(tmp);
	CHECK(tmp = ft_strsplit(ctime(&st.st_mtime), ' '));
	c_time = ft_fill_date(tmp);
	new->print_date = ((n_time[0] > c_time[0]) || ((n_time[1] - c_time[1]) > 6)
			|| ((n_time[1] - c_time[1]) == 6 && (n_time[2] - c_time[2]) > 0)) ?
			formatdate(tmp, 1) : formatdate(tmp, 0);
	ft_strdl2(tmp);
	free(c_time);
	free(n_time);
	return (0);
}

char	parse_type(struct stat	st)
{
	if (S_ISDIR(st.st_mode) == 1)
		return ('d');
	else if (S_ISLNK(st.st_mode) == 1)
		return ('l');
	else if (S_ISFIFO(st.st_mode) == 1)
		return ('m');
	else if (S_ISSOCK(st.st_mode) == 1)
		return ('s');
	else if (S_ISCHR(st.st_mode) == 1)
		return ('c');
	else if (S_ISBLK(st.st_mode))
		return ('b');
	else
		return ('f');
}

char	parse_symb(char *d_name)
{
	ssize_t len;
	acl_t	acl;
	int		l_attr;
	int		l_acl;

	len = listxattr(d_name, NULL, 0, XATTR_NOFOLLOW);
	acl = acl_get_file(d_name, ACL_TYPE_EXTENDED);
	l_attr = (len > 0) ? 1 : 0;
	l_acl = (acl) ? 1 : 0;
	acl_free((void *)acl);
	if (l_attr)
		return ('@');
	else
		return (l_acl ? '+' : ' ');
}

int		ft_new_curr(char *d_name, t_fl **fl, t_curr **cur, char *path)
{
	t_curr		*new;
	char		*p;
	struct stat	st;
	int			check;

	CHECK(new = (t_curr *)malloc(sizeof(t_curr)));
	p = (path) ? ft_strjoin(path, d_name) : d_name;
	if (path && !p)
		return (ft_er1(&new));
	if (lstat(p, &st))
		return (er2(&new, path, &p, 13));
	new->type = parse_type(st);
	new->symb = ((*fl)->l == 1 ? parse_symb(p) : ' ');
	if ((parse_name(new, d_name, p, fl)) == -1)
		return (-1);
	check = ((*fl)->l == 1) ? parse_else(new, st) : ft_parse_null(new);
	if (check == -1)
		return (er2(&new, path, &p, 0));
	if (((*fl)->l == 1 || (*fl)->t == 1))
		check = parse_date(new, fl, st);
	if (check == -1)
		return ((*fl)->l == 1 ? er2(&new, path, &p, 1) : er2(&new, path, &p, 0));
	CHECKM(path, free(p));
	ft_lstaddcu(cur, new);
	return (0);
}
