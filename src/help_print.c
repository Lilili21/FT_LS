/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 14:04:16 by gfoote            #+#    #+#             */
/*   Updated: 2019/07/31 14:04:18 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsft.h"

int			ft_order(int num)
{
	int order;

	order = 1;
	while (num > 9)
	{
		num /= 10;
		order++;
	}
	return (order);
}

size_t		ft_max_name(t_curr *curr_dir)
{
	size_t max;

	max = 0;
	while (curr_dir)
	{
		max += ft_strlen(curr_dir->name) + 1;
		curr_dir = curr_dir->next;
	}
	return (max);
}

int			ft_compare(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

t_count		*ft_count_s(t_curr *curr_dir, int fl)
{
	t_count	*max_s;

	if (!(max_s = (t_count *)malloc(sizeof(t_count))))
		return (NULL);
	max_s->s_links = 0;
	max_s->s_user = 0;
	max_s->s_groop = 0;
	max_s->s_size = 0;
	max_s->total = 0;
	max_s->s_name = (fl == 0) ? ft_max_name(curr_dir) : 0;
	if (fl == 0)
		return (max_s);
	while (curr_dir)
	{
		max_s->s_links = ft_compare(ft_order(curr_dir->links), max_s->s_links);
		max_s->s_user = ft_compare((int)ft_strlen(curr_dir->user),
				max_s->s_user);
		max_s->s_groop = ft_compare((int)ft_strlen(curr_dir->groop),
				max_s->s_groop);
		max_s->s_size = ft_compare(ft_order(curr_dir->size), max_s->s_size);
		max_s->total += curr_dir->s_total;
		curr_dir = curr_dir->next;
	}
	return (max_s);
}


