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
/*
int		ft_size_dirr_p(t_curr **curr_dir)
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
}*/

int			ft_str_int(int num)
{
	int order;

	order = 0;
	while (num > 0)
	{
		num /= 10;
		order++;
	}
	return (order);
}

t_count		*ft_count_s(t_curr *curr_dir)
{
	t_count	*count_col;

	if (!(count_col = (t_count *)malloc(sizeof(t_count *))))
		return (NULL);
	count_col->s_name = 0;
	count_col->s_links = 0;
	count_col->s_user = 0;
	count_col->s_groop = 0;
	count_col->s_size = 0;
	while (curr_dir)
	{
		count_col->s_name = (ft_strlen(curr_dir->name) > count_col->s_name)
							? ft_strlen(curr_dir->name) : count_col->s_name;
		count_col->s_links = (ft_str_int(curr_dir->links) > count_col->s_links)
							 ? ft_str_int(curr_dir->links) : count_col->s_links;
		count_col->s_user = (ft_strlen(curr_dir->user) > count_col->s_user)
							? ft_strlen(curr_dir->user) : count_col->s_user;
		count_col->s_groop = (ft_strlen(curr_dir->groop) > count_col->s_groop)
							 ? ft_strlen(curr_dir->groop) : count_col->s_groop;
		count_col->s_size = (ft_str_int(curr_dir->size) > count_col->s_size)
							? ft_str_int(curr_dir->size) : count_col->s_size;
		curr_dir = curr_dir->next;
	}
	return (count_col);
}