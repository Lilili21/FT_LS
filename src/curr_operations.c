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

t_curr	*ft_new_curr(dirent	*rd)
{
	t_curr *new;

	if (!(new = (t_list *)malloc(sizeof(t_curr))))
		return (NULL);
	new->type = rd->d_type;
	new->rights = NULL;
	new->links = 0;
	new->user = NULL;
	new->groop = NULL;
	new->size = 0;
	new->date = NULL;
	new->name = NULL;
	new->next = NULL;
	return (new);
}

void	ft_add(t_curr **curr_dir, t_curr *new)
{
	if (!curr_dir || !new)
		return ;

}

void ft_add_sorted(t_curr **curr_dir, struct dirent *rd, t_fl **fl)

{
	t_curr *current;
	t_curr *new;
	int sort_order;

	current = *curr_dir;
	new = ft_new_curr(rd);
	sort_order = (global_flags & (1 << 4)) ? -1 : 1;

	if (global_flags & (1 << 3)) //если t
	{
		//sort data;
	}
	else
	{
		if (sort_order * ft_strcmp(current->name, new->name) > 0)
		{
			new->next = (*curr_dir);
			(*curr_dir) = new;
		}
		else
		{
			while (current->next != NULL && sort_order * ft_strcmp(current->next->name, new->name) < 0)
				current = current->next;
			if (current->next != NULL)
				new->next = current->next;
			current->next = new;
		}
	}
}