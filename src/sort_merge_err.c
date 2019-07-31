/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_merge_err.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 14:35:31 by gfoote            #+#    #+#             */
/*   Updated: 2019/07/26 14:35:33 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsft.h"

int		ft_size_dirr_err(t_err **curr_dir)
{
	int		count;
	t_err		*curr;

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

void	ft_front_back_split_err(t_err *source, t_err **front_l, t_err **back_l)
{
	int		len;
	int		i;
	int		middle;
	t_err	*current;

	current = source;
	len = ft_size_dirr_err(source);
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

t_err	*ft_sorted_merge_err(t_err *a, t_err *b)
{
	t_err *result;

	*result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (ft_strcmp(a->name, b->name) > 0)
	{
		result = a;
		result->next = ft_sorted_merge_err(a->next, b);
	}
	else
	{
		result = b;
		result->next = ft_sorted_merge_err(a, b->next);
	}
	return (result);
}

void	ft_merge_sort_err(t_err **que)
{
	t_err *head;
	t_err *a;
	t_err *b;

	head = *que;
	if ((head == NULL) || (head->next == NULL))
		return ;
	ft_front_back_split_err(head, &a, &b);
	ft_merge_sort_err(&a);
	ft_merge_sort_err(&b);
	*que = ft_sorted_merge_err(a, b);
}
