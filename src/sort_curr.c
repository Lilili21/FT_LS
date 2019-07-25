/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curr_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 18:00:29 by gfoote            #+#    #+#             */
/*   Updated: 2019/07/19 18:00:31 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsft.h"

int		ft_size_dirr(t_curr **curr_dir)
{
	int 	count;
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

t_curr	**ft_list_to_int(t_curr **curr_dir, int size)
{
	t_curr	**sort;
	t_curr	*current;
	int		i;

	i = -1;
	current = *curr_dir;
	sort = (t_curr **)malloc(sizeof(char) * ft_size_dirr(curr_dir));
	while (++i < size)
	{
		sort[i] = current;
		current = current->next;
	}
	return (sort);
}

int	ft_swap_curr(t_curr *a, t_curr *b)
{
	t_curr c;

	c = *a;
	*a = *b;
	*b = c;
	return (1);
}

void	ft_sort(t_curr **curr_dir, int s_order, int type)
{
	t_curr	**sort;
	t_curr	*current;
	int		i;
	int		check;

	if (ft_size_dirr(curr_dir) > 1)
	{
		sort = ft_list_to_int(curr_dir, ft_size_dirr(curr_dir));
		check = 1;
		while (check)
		{
			i = -1;
			check = 0;
			while (++i < ft_size_dirr(curr_dir) - 1)
				if ((type == "name" && s_order * ft_strcmp(sort[i]->name, sort[i + 1]->name) > 0) ||
				(type == "time" &&
				(s_order * (sort[i]->compare_date - sort[i + 1]->compare_date) > 0 ||
				(s_order * (sort[i]->compare_date - sort[i + 1]->compare_date) == 0 &&
				ft_strcmp(sort[i]->name, sort[i + 1]->name) > 0))))
					check = ft_swap_curr(sort[i], sort[i + 1]);
		}
		i = 0;
		current = sort[0];
		while (++i < ft_size_dirr(curr_dir) - 1)
		{
			current->next = sort[i];
			current = current->next;
		}
		current->next = NULL;
	}
}

void ft_sort2(t_curr **curr_dir, int s_order, int type)
{

}