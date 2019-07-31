/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_merge_q.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 14:35:31 by gfoote            #+#    #+#             */
/*   Updated: 2019/07/26 14:35:33 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsft.h"

int		ft_size_dirr_q(t_q **curr_dir)
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

void	ft_front_back_split_q(t_q *source, t_q **front_l, t_q **back_l)
{
	int		len;
	int		i;
	int		middle;
	t_q	*current;

	current = source;
	len = ft_size_dirr_q(&source);
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

t_q	*ft_sorted_merge_q(t_q *a, t_q *b, int sort_order, int type)
{
	t_q *result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if ((type == 0 && sort_order * ft_strcmp(a->abspath, b->abspath) > 0) ||
		(type == 1 && (sort_order * (a->compare_date - b->compare_date) > 0 ||
	   (sort_order * (a->compare_date - b->compare_date) == 0 &&
	   ft_strcmp(a->abspath, b->abspath) > 0))))
	{
		result = a;
		result->next = ft_sorted_merge_q(a->next, b, sort_order, type);
	}
	else
	{
		result = b;
		result->next = ft_sorted_merge_q(a, b->next, sort_order, type);
	}
	return (result);
}

void	ft_merge_sort_q(t_q **que, t_fl *fl)
{
	t_q *head;
	t_q *a;
	t_q *b;

	head = *que;
	if ((head == NULL) || (head->next == NULL))
		return ;
	ft_front_back_split_q(head, &a, &b);
	ft_merge_sort_q(&a, fl);
	ft_merge_sort_q(&b, fl);
	*que = ft_sorted_merge_q(a, b, fl->r, fl->t);
}
