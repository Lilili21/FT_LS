/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_print4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 14:57:24 by gfoote            #+#    #+#             */
/*   Updated: 2019/08/27 14:57:26 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsft.h"
#include <stdio.h>

void	total(t_count *count)
{
	write(1, "total ", 6);
	ft_putnbr(count->total);
	write(1, "\n", 1);
}

int		ft_buff_size(t_curr *curr_dir, t_count *count)
{
	int		buff_size;

	buff_size = ft_size_dirr(&curr_dir) * (32 + count->maj + count->s_links +
			count->s_user + count->s_groop + count->s_size + count->s_name);
	if (buff_size > 500)
		buff_size = 500;
	return (buff_size);
}

int		ft_print_column2(t_curr *curr, t_count *count)
{
	char	*print;
	int		i;

	if (!(print = ft_strnew(count->total)))
		return (-1);
	i = 0;
	while (curr)
	{
		i = ft_strjoin_char_0(print, i, curr->name, ft_strlen(curr->name));
		print[i++] = '\n';
		curr = curr->next;
	}
	print[i] = '\0';
	ft_putstr(print);
	free(print);
	return (0);
}
