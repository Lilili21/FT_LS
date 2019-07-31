/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:17:58 by gfoote            #+#    #+#             */
/*   Updated: 2019/07/25 17:18:00 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsft.h"

void	ft_add_curr(t_curr **curr_dir, t_curr *new)
{
	if (!*curr_dir || !new)
		return ;
	new->next = (*curr_dir);
	(*curr_dir) = new;
}

void	ft_free(t_curr **curr)
{
	if ((*curr)->rights != NULL)
		free((*curr)->rights);
	if ((*curr)->check_date % 10 == 2)
		free((*curr)->print_date);
	free((*curr));
}

t_q		*ft_new_q(t_curr *current, int lev)
{
	t_q *new;

	if (!(new = (t_q *)malloc(sizeof(t_q))))
		return (NULL);
	new->abspath = NULL;
	new->next = NULL;
	return (new);
}
/*
void	ft_fill_que(t_curr **curr_dir, t_q **que, char *av)
{
	t_q		*q_first;
	t_curr	*curr;
	t_curr	*tmp;

	curr = *curr_dir;
	q_first = NULL;
	while (curr)
	{
		if (curr->type == 'd' && q_first == NULL)
		{
			q_first = ft_new_q(curr, (*que)->lev + 1);
			start = q_first;
		}
		else if (curr->type == 'd' && q_first != NULL)
			q_first->next = ft_new_q(curr, (*que)->lev + 1);
		q_first = q_first->next;
		tmp = curr->next;
		ft_free(curr);
		curr = tmp;
	}
	if (q_first != NULL)
		q_first->next = *que;		
}
*/