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

void	ft_strdl2(char **tmp)
{
	ft_strdl(tmp);
	free(tmp);
}

int		type_check(char c)
{
	if (c == 'b' || c == 'c')
		return (1);
	return (0);
}

void	ft_parse_null(t_curr *new)
{
	new->rights = NULL;
	new->links = 0;
	new->user = NULL;
	new->groop = NULL;
	new->size = 0;
	new->maj = -1;
	new->s_total = 0;
	new->print_date = 0;
}

char	*formatdate(char **str, int check)
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
			result[i++] = str[j][k++];
		j++;
		if (ft_strlen(str[2]) == 1 && j == 2)
			result[i++] = ' ';
		if (i < 8)
			result[i++] = ' ';
		if (check == 1 && i == 7 && j++ == 3)
			result[i++] = ' ';
	}
	result[i] = '\0';
	return (result);
}
