/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 14:25:30 by gfoote            #+#    #+#             */
/*   Updated: 2019/08/28 14:25:35 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsft.h"

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

void	ft_parse_flags_null(t_fl *fl)
{
	fl->rr = 0;
	fl->a = 0;
	fl->l = 0;
	fl->r = -1;
	fl->t = 0;
	fl->c = 0;
	fl->prev = 0;
}
