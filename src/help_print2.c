/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_print2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:11:51 by gfoote            #+#    #+#             */
/*   Updated: 2019/08/22 16:11:53 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsft.h"
#include <stdio.h>

char	**ft_list_to_char(t_curr **curr_dir, int size)
{
	char	**sort;
	t_curr	*current;
	int		i;

	i = -1;
	current = *curr_dir;
	sort = (char**)malloc(sizeof(char *) * (size + 1)); //add check to NULL
	sort[size] = 0;
	while (++i < size)
	{
		sort[i] = ft_strdup(current->name); //add check to NULL
		current = current->next;
	}
	return (sort);
}

int		ft_check_eight(int number)
{
	if (number % 8 == 0)
		return (number + 8);
	else
		while (number % 8 != 0)
			number++;
	return (number);
}

void	ft_fill_result(char *result, char **new, int *param)
{
	int	i[4];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	i[3] = param[2];
	while (i[0] < param[3] && new[i[2]])
	{
		i[1] = ft_strjoin_char_2(result, i[1], new[i[2]], param[0]);
		ft_strdel(&new[i[2]]);
		i[3]--;
		i[2] += param[3];
		if (i[1] > param[1] * (i[0] + 1))
			while (result[i[1]] == ' ' && i[1] > param[1] * (i[0] + 1))
				i[1]--;
		if (i[3] == 0 || i[2] > param[4] - 1)
		{
			//printf("i[1] = %i\n", i[1]);
			result[i[1]++] = '\n';
			i[0]++;
			i[2] = i[0];
			i[3] = param[2];
		}
	}
	result[i[1]] = '\0';
}

int		ft_print_column(t_curr *curr, t_count *count)
{
	struct winsize	w;
	int				param[5];
	char			**new;
	char			*result;

	ioctl(0, TIOCGWINSZ, &w);
	param[0] = ft_check_eight(count->s_name);
	param[1] = w.ws_col; //width
	param[2] = (param[1] > 0 && (param[1] / param[0]) > 0) ?
			param[1] / param[0] : 1;  // number of columns
	param[3] = (count->s_size % param[2] == 0) ? count->s_size / param[2] :
			count->s_size / param[2] + 1; // number of lines
	param[4] = count->s_size; //number of elements
	new = ft_list_to_char(&curr, count->s_size);
	if (!(result = (char *)malloc(sizeof(char) * (param[1] * param[3] + 1))))
		return (-1);
	ft_fill_result(result, new, param);
	ft_putstr(result);
	if (new)
		free(new);
	free(result);
	return (0);
}
