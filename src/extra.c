/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 20:31:26 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/08/08 20:31:28 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsft.h"

int		print_err(t_err **err, t_fl **fl)
{
	t_err	*tmp;

	while (*err)
	{
		(*fl)->prev = 1;
		if (erp((*err)->name, (*err)->er))
			return (12);
		tmp = (*err)->next;
		free((*err)->name);
		free((*err)->er);
		free(*err);
		*err = tmp;
	}
	return (0);
}

char	*ft_strjspl(char *s1, char *s2)
{
	char	*b;
	size_t	i;
	size_t	s;
	char	*tmp;

	if (!s1 || !s2 || !(b = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	i = -1;
	s = 0;
	while (s1[++i])
		b[i] = s1[i];
	tmp = s2;
	s2 = ft_strrchr(s2, '/');
	if (s2)
		s2++;
	if (s2)
		;
	else
		s2 = tmp;
	while (s2[s])
		b[i++] = s2[s++];
	b[i] = '\0';
	return (b);
}

int		erp(char *av, char *er)
{
	char *b;
	char *tmp;

	if (av)
	{
		if (!(b = ft_strjspl("ls: ", av)))
			return (12);
		tmp = b;
		if (!(b = ft_strjoin(b, ": ")))
			return (12);
		free(tmp);
	}
	else
	{
		if (!(b = ft_strdup("ls: ")))
			return (12);
	}
	tmp = b;
	if (!(b = ft_strjoin(b, er)))
		return (12);
	free(tmp);
	ft_putendl_fd(b, 2);
	free(b);
	return (0);
}

int		pdir(char *av, int *prev)
{
	char *tmp;

	if (*prev == 4)
	{
		*prev = 2;
		return (0);
	}
	if (*prev == 2)
		write(1, "\n", 1);
	*prev = 2;
	if (!(tmp = ft_strjoin(av, ": ")))
		return (12);
	ft_putendl(tmp);
	free(tmp);
	return (0);
}

void	ft_free_one(t_curr **curr)
{
	if (!(*curr))
		return ;
	if ((*curr)->groop)
		ft_strdel(&(*curr)->groop);
	if ((*curr)->user)
		ft_strdel(&(*curr)->user);
	if ((*curr)->rights)
		ft_strdel(&(*curr)->rights);
	if ((*curr)->print_date)
		ft_strdel(&(*curr)->print_date);
	if ((*curr)->name)
		ft_strdel(&(*curr)->name);
	free((*curr));
	(*curr) = 0;
}

void	del_node(t_q **que)
{
	t_q	*tmp;

	tmp = (*que)->next;
	free((*que)->abspath);
	free(*que);
	*que = tmp;
}

void	ft_free(t_curr **curr, char **av)
{
	t_curr *tmp;

	if (av && *av)
		ft_strdel(av);
	if (!(*curr))
		return ;
	while (*curr)
	{
		if ((*curr)->groop)
			ft_strdel(&(*curr)->groop);
		if ((*curr)->user)
			ft_strdel(&(*curr)->user);
		if ((*curr)->rights)
			ft_strdel(&(*curr)->rights);
		if ((*curr)->print_date)
			ft_strdel(&(*curr)->print_date);
		if ((*curr)->name)
			ft_strdel(&(*curr)->name);
		tmp = (*curr)->next;
		free((*curr));
		(*curr) = tmp;
	}
}
