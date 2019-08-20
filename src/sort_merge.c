/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_merge.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 14:35:31 by gfoote            #+#    #+#             */
/*   Updated: 2019/07/26 14:35:33 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsft.h"

int		ft_size_dirr(t_curr **curr_dir)
{
	int		count;
	t_curr	*curr;

	count = 0;
	if (!*curr_dir)
		return (0);
	curr = *curr_dir;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

void	ft_front_back_split(t_curr *source, t_curr **front_l, t_curr **back_l)
{
	int		len;
	int		i;
	int		middle;
	t_curr	*current;

	current = source;
	len = ft_size_dirr(&source);
	i = -1;
	if (len < 2)
	{
		*front_l = source;
		*back_l = NULL;
	}
	else
	{
		middle = (len - 1) / 2;
		while (++i < middle)
			current = current->next;
		*front_l = source;
		*back_l = current->next;
		current->next = NULL;
	}
}

t_curr	*ft_sorted_merge(t_curr *a, t_curr *b, int sort_order, int type)
{
	t_curr *result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if ((type == 0 && sort_order * ft_strcmp(a->name, b->name) > 0) ||
	(type == 1 && (sort_order * (a->compare_date - b->compare_date) < 0 ||
	(sort_order * (a->compare_date - b->compare_date) == 0
	&& sort_order * ft_strcmp(a->name, b->name) > 0))))
	{
		result = a;
		result->next = ft_sorted_merge(a->next, b, sort_order, type);
	}
	else
	{
		result = b;
		result->next = ft_sorted_merge(a, b->next, sort_order, type);
	}
	return (result);
}

void	ft_merge_sort(t_curr **curr_dir, t_fl *fl)
{
	t_curr *head;
	t_curr *a;
	t_curr *b;

	head = *curr_dir;
	if ((head == NULL) || (head->next == NULL))
		return ;
	ft_front_back_split(head, &a, &b);
	ft_merge_sort(&a, fl);
	ft_merge_sort(&b, fl);
	*curr_dir = ft_sorted_merge(a, b, fl->r, fl->t);
}
