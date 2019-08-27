/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 15:32:01 by gfoote            #+#    #+#             */
/*   Updated: 2019/08/09 16:42:59 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsft.h"

int		ft_strjoin_space(char *result, int i, int space_number)
{
	int j;

	j = -1;
	while (++j < space_number)
		result[i++] = ' ';
	return (--i);
}

char	*ft_fill_str(t_curr *curr, int size, t_count *count_col)
{
	char	*result;
	int		i;

	i = 0;
	if (!(result = ft_strnew(size)))
		return (NULL);
	i = ft_fill_str1(curr, count_col, i, result);
	i = ft_fill_str2(curr, count_col, i, result);
	result[i++] = '\n';
	result[i] = '\0';
	return (result);
}

int		ft_print_folder(t_curr **curr, t_count *count, int buff_size)
{
	char	*result;
	char	*tmp;
	int		str_size;
	int		i;

	i = 0;
	if (!(result = ft_strnew(buff_size)))
		return (-1);
	while (*curr)
	{
		str_size = 32 + count->maj + count->s_links + count->s_user +
			count->s_groop + count->s_size + ft_strlen((*curr)->name);
		if (buff_size - str_size < 0)
			break ;
		if (!(tmp = ft_fill_str(*curr, str_size, count)))
			return (ft_mistake(result));
		i = ft_strjoin_char_1(result, i, tmp, str_size);
		free(tmp);
		*curr = (*curr)->next;
		buff_size -= str_size;
	}
	result[i] = '\0';
	write(1, result, ft_strlen(result));
	free(result);
	return (0);
}

int		ft_print(t_curr *curr_dir, t_fl *fl)
{
	t_count *count;
	int		buff_size;
	int		check;

	check = 0;
	if (!curr_dir)
		return (0);
	if (!(count = ft_count_s(curr_dir, fl->l)))
		return (-1);
	if (fl->l == 1)
	{
		if (fl->prev == 2)
			total(count);
		buff_size = ft_buff_size(curr_dir, count);
		while (curr_dir && check == 0)
			check = ft_print_folder(&curr_dir, count, buff_size);
	}
	else if (fl->c == 1)
		check = ft_print_column2(curr_dir, count);
	else
		check = ft_print_column(curr_dir, count);
	free(count);
	return (check);
}
