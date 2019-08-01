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

void	ft_free(t_curr **curr)
{
	t_curr *tmp;

	if (!(*curr))
		return ;
	while(*curr)
	{
		if ((*curr)->rights != NULL)
			free((*curr)->rights);
		if ((*curr)->check_date % 10 == 2)
			free((*curr)->print_date);
		tmp = (*curr)->next;
		free((*curr));
		(*curr) = tmp;
	}
}