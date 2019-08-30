/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 18:59:43 by gfoote            #+#    #+#             */
/*   Updated: 2019/08/28 18:59:46 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsft.h"

int		parse_else(t_curr *new, struct stat st)
{
	new->s_total = st.st_blocks;
	new->links = st.st_nlink;
	new->size = type_check(new->type) ? minor(st.st_rdev) : st.st_size;
	new->maj = type_check(new->type) ? major(st.st_rdev) : -1;
	CHECK(new->user = ft_strdup(getpwuid(st.st_uid)->pw_name));
	new->groop = ft_strdup(getgrgid(st.st_gid)->gr_name);
	new->next = NULL;
	if (!new->groop)
	{
		free(new->user);
		return (-1);
	}
	new->rights = (char *)malloc(sizeof(char) * 11);
	if (!new->rights)
	{
		free(new->user);
		free(new->groop);
		return (-1);
	}
	parse_rights(st, new);
	return (0);
}

int		ft_er1(t_curr **new)
{
	free(*new);
	perror("ft_ls: ");
	return (-1);
}

int		er2(t_curr **new, char *path, char **p, int check)
{
	if (check == 1)
	{
		free((*new)->groop);
		free((*new)->user);
		free((*new)->rights);
	}
	CHECKM(path, free(*p));
	if (check == 13)
	{
		free(*new);
		return (0);
	}
	return (ft_er1(new));
}

int		ft_er3(char *d_name, char *p, t_curr **new)
{
	if (!ft_strequ(p, d_name))
		free(p);
	return (ft_er1(new));
}
