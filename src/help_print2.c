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
	sort = malloc(sizeof(char *) * size);
	while (++i < size + 1)
	{
		sort[i] = ft_strdup(current->name);
		current = current->next;
	}
	return (sort);
}

int		ft_print_column(t_curr	*curr, t_count *count)
{
	struct winsize	w;
	int 			column; //column wide
	int 			str_count;
	char			**new;
	char			*result;
	int 			i[3];

	ioctl(0, TIOCGWINSZ, &w);
	column = w.ws_col / (count->s_name + 5);
	//column = 10; // number of columns
	str_count = count->s_size / column; // number of lines
	new = ft_list_to_char(&curr, count->s_size); // array of files to print
	i[0] = 0; // number of raw
	i[1] = 0; // place in the result array
	i[2] = 0; // number from new array
	result = (char *)malloc(sizeof(char) *  425 * str_count); // w.ws_col * str_count); // result array
	while(i[0] < str_count + 1 && new[i[2]]) //i0 < number of strings and exist an element to print
	{
		i[1] = ft_strjoin_char_2(result, i[1], new[i[2]], count->s_name + 2); //
		//i[1]++;
		i[2] += str_count;
		if ( (i[2] % (column - str_count + 1) == 0 && i[2] != str_count) || !new[i[2]])
		{
			result[i[2]] = '\n';
			i[0]++;
			i[2] =i[0];
		}
	}
	result[i[1]] = '\0';
	write(1, result, ft_strlen(result));
	free(result);
	return (0);
}

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
		buff_size = 1000;
	return (buff_size);
}
/*
int		ft_print_column(t_curr *curr, t_count *count)
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
}*/

int		ft_fill_str1(t_curr *curr, t_count *count_col, int i, char *result)
{
	char	*tmp;

	i = ft_strjoin_char_1(result, i, curr->rights, ft_strlen(curr->rights));
	result[i] = curr->symb;
	i = ft_strjoin_space(result, ++i, 2);
	tmp = ft_itoa(curr->links);
	i = ft_strjoin_char_0(result, i, tmp, count_col->s_links);
	free(tmp);
	i = ft_strjoin_space(result, i, 2);
	i = ft_strjoin_char_2(result, i, curr->user, count_col->s_user);
	i = ft_strjoin_space(result, i, 3);
	i = ft_strjoin_char_2(result, i, curr->groop, count_col->s_groop);
	i = ft_strjoin_space(result, i, 3);
	return (i);
}

int		ft_fill_str2(t_curr *curr, t_count *count_col, int i, char *result)
{
	char	*tmp;

	if (curr->type == 'b' || curr->type == 'c')
	{
		tmp = ft_itoa(curr->maj);
		tmp = ft_sfstrjoin(&tmp, ",");
		i = ft_strjoin_char_0(result, i, tmp, count_col->maj);
		free(tmp);
		i = ft_strjoin_space(result, i, 2);
	}
	else if (count_col->maj > 0)
		i = ft_strjoin_space(result, i, count_col->maj + 2);
	else
		ft_strjoin_char_0(result, i, 0, count_col->maj);
	tmp = ft_itoa(curr->size);
	i = ft_strjoin_char_0(result, i, tmp, count_col->s_size);
	free(tmp);
	i = ft_strjoin_space(result, i, 1);
	i = ft_strjoin_char_0(result, i, curr->print_date, 13);
	i = ft_strjoin_space(result, i, 2);
	i = ft_strjoin_char_0(result, i, curr->name, ft_strlen(curr->name));
	return (i);
}
