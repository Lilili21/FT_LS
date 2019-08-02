/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 15:32:01 by gfoote            #+#    #+#             */
/*   Updated: 2019/07/26 15:32:03 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsft.h"
#include <stdio.h>

int		ft_strjoin_space(char *result, int i, int space_number)
{
	int j;

	j = -1;
	while (++j < space_number)
		result[i++] = ' ';
	return (--i);
}

int		ft_strjoin_char(char *result, int i, char *src, int m_size)
{
	int j;
	int src_size;

	j = 0;
	src_size = ft_strlen(src);
	if (src_size < m_size + 1)
		i = ft_strjoin_space(result, i, m_size - src_size);
	while (j < src_size + 1)
		result[++i] = src[j++];
	return (i);
}

char	*ft_fill_str(t_curr *current, int size, t_count *count_col)
{
	char	*result;
	int		i;

	i = -1;
	if (!(result = ft_strnew(size)))
		return (NULL);
	i = ft_strjoin_char(result, i, current->rights, 11);
	result[i] = current->symb;
	i = ft_strjoin_space(result, ++i, 2);
	i = ft_strjoin_char(result, i, ft_itoa(current->links), count_col->s_links);
	i = ft_strjoin_space(result, i, 2);
	i = ft_strjoin_char(result, i, current->user, count_col->s_user);
	i = ft_strjoin_space(result, i, 3);
	i = ft_strjoin_char(result, i, current->groop, count_col->s_groop);
	i = ft_strjoin_space(result, i, 3);
	i = ft_strjoin_char(result, i, ft_itoa(current->size), count_col->s_size);
	i = ft_strjoin_space(result, i, 1);
	i = ft_strjoin_char(result, i, current->print_date, 13);
	i = ft_strjoin_space(result, i, 2);
	i = ft_strjoin_char(result, i, current->name, ft_strlen(current->name));
	result[i++] = '\n';
	result[i] = '\0';
	return (result);
}

t_curr	*ft_print_folder(t_curr *curr, t_count *count, int buff_size)
{
	char	*result;
	char	*tmp;
	int		str_size;
	int		i;

	i = 0;
	if (!(result = ft_strnew(buff_size)))
		return (ft_mistake(NULL));
	while (curr)
	{
		str_size = 32 + count->s_links + count->s_user +
				count->s_groop + count->s_size + ft_strlen(curr->name);
		if (buff_size - str_size < 0)
			break ;
		if (!(tmp = ft_fill_str(curr, str_size, count)))
			return (ft_mistake(result));
		i = ft_strjoin_char(result, i, tmp, str_size);
		free(tmp);
		curr = curr->next;
		buff_size -= str_size;
	}
	result[i] = '\n';
	write(1, result, ft_strlen(result));
	free(result);
	return (curr);
}

int		ft_print(t_curr *curr_dir, t_fl *fl)
{
	t_count *count;
	t_curr	*curr;
	char	*print;
	int		str_size;
	int		size_dir;
	int		buff_size;
	int		i;


	curr = curr_dir;
	if (!(count = ft_count_s(curr_dir, fl->l)))
		return (-1);
	if (fl->l == 1)
	{
			write(1, "total ", 6);
			ft_putnbr(count->total);
			write(1, "\n", 1);
			size_dir = ft_size_dirr(&curr);
			str_size = 32 + count->s_links + count->s_user +
					   count->s_groop + count->s_size + count->s_name;
			buff_size = (size_dir * str_size > 100) ? 100 : size_dir * str_size;
			while (curr)
				curr = ft_print_folder(curr, count, buff_size);
	}
	else
	{
		if (!(print = ft_strnew(count->s_name)))
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
	}
		free(count);
	return (0);
}
