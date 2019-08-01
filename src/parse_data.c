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
#include <stdio.h>
int		parse_rights(t_curr *new, char *d_name)
{
	struct stat	st;

	if (lstat(d_name, &st))
		return (errno);
	new->links = st.st_nlink;
	new->size = st.st_size;
	new->user = getpwuid(st.st_uid)->pw_name;
	new->groop = getgrgid(st.st_gid)->gr_name;
	new->rights = (char *)malloc(11);
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

char	*formatdate(char **str)
{
	char	*result;
	int		i;
	int		j;
	int		k;

	result = (char *)malloc(sizeof(char) * 13);
	i = 0;
	j = 1;
	while (i < 10)
	{
		k = 0;
		while (str[j][k] && i < 12)
		{
			result[i] = str[j][k];
			i++;
			k++;
		}
		j++;
		if (ft_strlen(str[2]) == 1 && j == 2)
			result[i++] = ' ';
		if (i < 8)
			result[i++] = ' ';
	}
	result[i] = '\0';
	return (result);
}

int	parse_date(t_curr *new, char *d_name, t_fl **fl)
{
	struct stat	st;

	if (lstat(d_name, &st))
		return (errno);
	if ((*fl)->t == 1)
	{
		new->check_date += 10;
		new->compare_date = st.st_mtimespec.tv_sec;
	}
	if ((*fl)->l == 1)
	{
		new->check_date += 2;
		new->print_date = formatdate(ft_strsplit(ctime(&st.st_mtime), ' '));
	}
	return (0);
}

char	parse_type(char *d_name)
{
	struct stat	st;

	if (lstat(d_name, &st))
	{
		perror("ls: ");
		return ('E');
	}
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
	if (l_acl && l_attr)
		return ('@');
	else if (l_acl)
		return('+');
	else if (l_attr)
		return ('@');
	else
		return (' ');
}

int		ft_new_curr(char *d_name, t_fl **fl, t_curr **cur, char *path)
{
	t_curr		*new;
	char		*p;

	p = NULL;
	if (!(new = (t_curr *)malloc(sizeof(t_curr))))
		return (0);
	new->name = ft_strdup(d_name);
	if (path)
	{
		p = path[ft_strlen(path) - 1] == '/' ? path : ft_strjoin(path, "/");
		p = ft_strjoin(p, d_name); //add protection
	}
	new->type = (p == 0 ? parse_type(d_name) : parse_type(p));
	new->symb = ((*fl)->l == 1 ? parse_symb(p) : ' ');
	printf("%c = c %s\n",new->symb, new->name);

	if (new->type == 'E')
		return (0);
	new->next = NULL;
	new->check_date = 0;
	if ((*fl)->l == 1)
		parse_rights(new, d_name);
	else
	{
		new->rights = NULL;
		new->links = 0;
		new->user = NULL;
		new->groop = NULL;
		new->size = 0;
	}
	if ((*fl)->l == 1 || (*fl)->t == 1)
		parse_date(new, d_name, fl);
	ft_lstaddcu(cur, new);
	return (1);
}
