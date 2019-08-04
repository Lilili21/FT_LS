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

int		parse_rights(t_curr *new, char *d_name)
{
	struct stat	st;

	if (lstat(d_name, &st))
		return (errno);
	new->links = st.st_nlink;
	new->size = st.st_size;
	new->user = ft_strdup(getpwuid(st.st_uid)->pw_name);
	new->groop = ft_strdup(getgrgid(st.st_gid)->gr_name);
	new->s_total = st.st_blocks;
	new->rights = (char *)malloc(sizeof(char) * 11);
	new->rights[0] = (new->type == 'f') ? '-' : new->type;
	new->rights[1] = (st.st_mode & S_IRUSR) ? 'r' : '-';
	new->rights[2] = (st.st_mode & S_IWUSR) ? 'w' : '-';
	new->rights[3] = (st.st_mode & S_IXUSR) ? 'x' : '-';
	new->rights[4] = (st.st_mode & S_IRGRP) ? 'r' : '-';
	new->rights[5] = (st.st_mode & S_IWGRP) ? 'w' : '-';
	new->rights[6] = (st.st_mode & S_IXGRP) ? 'x' : '-';
	new->rights[7] = (st.st_mode & S_IROTH) ? 'r' : '-';
	new->rights[8] = (st.st_mode & S_IWOTH) ? 'w' : '-';
	new->rights[9] = (st.st_mode & S_IXOTH) ? 'x' : '-';
	new->rights[10] = '\0';
	return (0);
}

int		parse_date(t_curr *new, char *d_name, t_fl **fl)
{
	struct stat	st;

	if (lstat(d_name, &st))
		return (errno);
	if ((*fl)->t == 1)
		new->compare_date = st.st_mtimespec.tv_sec;
	if ((*fl)->l == 1)
		new->print_date = formatdate(ft_strsplit(ctime(&st.st_mtime), ' '));
	return (0);
}

char	parse_type(t_curr *new, char *d_name)
{
	struct stat	st;

	if (lstat(d_name, &st))
	{
		perror("ls: ");
		return ('E');
	}
	new->check_folder = 0;
	if (S_ISDIR(st.st_mode) == 1)
	{
		return ('d');
	}
	else if (S_ISLNK(st.st_mode) == 1)
		return ('l');
	else if (S_ISFIFO(st.st_mode) == 1)
		return ('m');
	else if (S_ISSOCK(st.st_mode) == 1)
		return ('s');
	else if (S_ISCHR(st.st_mode) == 1)
		return ('c');
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

//@ - имеет альтернативные расширения
//+ - имеет другие способы доступа

int		ft_new_curr(char *d_name, t_fl **fl, t_curr **cur, char *path)
{
	t_curr		*new;
	char		*p;

	p = NULL;
	if (!(new = (t_curr *)malloc(sizeof(t_curr))))
		return (0);
	new->name = ft_strdup(d_name);
	if (path)
		p = ft_strjoin(path, d_name);
	else
		p = d_name;
	new->type = parse_type(new, p);
	new->symb = ((*fl)->l == 1 ? parse_symb(p) : ' ');
	if (new->type == 'E')
		return (0);
	new->next = NULL;
	((*fl)->l == 1) ? parse_rights(new, p) : ft_parse_null(new);
	if ((*fl)->l == 1 || (*fl)->t == 1)
		parse_date(new, p, fl);
	ft_lstaddcu(cur, new);
	return (0);
}
