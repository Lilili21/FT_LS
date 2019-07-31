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

int		ft_size_dirr(t_q **curr_dir)
{
	int		count;
	t_q		*curr;

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

void	ft_front_back_split(t_q *source, t_q **front_l, t_q **back_l)
{
	int		len;
	int		i;
	int		middle;
	t_q	*current;

	current = source;
	len = ft_size_dirr(source);
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

t_q	*ft_sorted_merge(t_q *a, t_q *b, int sort_order)
{
	t_q *result;

	*result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (sort_order * ft_strcmp(a->abspath, b->abspath) > 0)
	{
		result = a;
		result->next = ft_sorted_merge(a->next, b, sort_order);
	}
	else
	{
		result = b;
		result->next = ft_sorted_merge(a, b->next, sort_order);
	}
	return (result);
}

void	ft_merge_sort(t_q **que, int sort_order)
{
	t_q *head;
	t_q *a;
	t_q *b;

	head = *que;
	if ((head == NULL) || (head->next == NULL))
		return ;
	ft_front_back_split(head, &a, &b);
	ft_merge_sort(&a, sort_order);
	ft_merge_sort(&b, sort_order);
	*que = ft_sorted_merge(a, b, sort_order);
}
