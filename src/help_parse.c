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

void	ft_parse_null(t_curr *new)
{
	new->rights = NULL;
	new->links = 0;
	new->user = NULL;
	new->groop = NULL;
	new->size = 0;
	new->maj = 0;
	new->s_total = 0;
	new->print_date = 0;
}

char	*formatdate(char **str)
{
	char	*result;
	int		i;
	int		j;
	int		k;

	result = (char *)malloc(sizeof(char) * 13);
	i = 0;
	j = 1;
	while (i < 10)
	{
		k = 0;
		while (str[j][k] && i < 12)
		{
			result[i] = str[j][k];
			i++;
			k++;
		}
		j++;
		if (ft_strlen(str[2]) == 1 && j == 2)
			result[i++] = ' ';
		if (i < 8)
			result[i++] = ' ';
	}
	result[i] = '\0';
	return (result);
}
/*
 * // в зависимости от столбца добавлять в место i т.е. маллочить огромную строку и вставлять в серединке
int		ft_print_column(t_curr	*curr, t_count *count, int size_dirr)
{
	char			*print;
	int				i;
	struct winsize	w;
	int 			column;
	int 			str;

	i = 0;
	ioctl(0, TIOCGWINSZ, &w);
	column = w.ws_col/count->s_name;
	str = size_dirr / column;
	if (column < 1)
		print = ft_strnew(count->total);
	else
		print = ft_strnew(str * w.ws_row);
	if (!print)
		return (-1);
	while (curr)
	{
		i = ft_strjoin_char(print, i, curr->name, ft_strlen(curr->name));
		print[i++] = '\n';
		curr = curr->next;
	}
	print[i] = '\0';
	ft_putstr(print);
	free(print);
	return (0);
}*/

int		ft_print_column(t_curr	*curr, t_count *count)
{
	char	*print;
	int		i;

	if (!(print = ft_strnew(count->total)))
		return (-1);
	i = 0;
	while (curr)
	{
		i = ft_strjoin_char(print, i, curr->name, ft_strlen(curr->name));
		print[i++] = '\n';
		curr = curr->next;
	}
	print[i] = '\0';
	ft_putstr(print);
	free(print);
	return (0);
}