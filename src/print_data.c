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

int 	ft_strjoin_space(char *result, int i, int space_number)
{
	int j;

	j = -1;
	while(++j < space_number)
	{
		result[i] = ' ';
		i++;
	}
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
	while(j < src_size + 1)
	{
		i++;
		result[i] = src[j++];
	}
	return (i);
}

void 	ft_strprint_join(t_curr *current, int size, t_count *count_col)
{
	char *result;
	int i;

	i = -1;
	if (!(result = ft_strnew(size)))
		return ;
	i = ft_strjoin_char(result, i, current->rights, 11);
	i++;
	result[i++] = current->symb;
	i = ft_strjoin_space(result, i, 2);
	i = ft_strjoin_char(result, i, ft_itoa(current->links), count_col->s_links);
	i = ft_strjoin_space(result, i, 2);
	i = ft_strjoin_char(result, i, current->user, count_col->s_user);
	i = ft_strjoin_space(result, i, 3);
	i = ft_strjoin_char(result, i, current->groop, count_col->s_groop);
	i = ft_strjoin_space(result, i, 3);
	i = ft_strjoin_char(result, i,  ft_itoa(current->size), count_col->s_size);
	i = ft_strjoin_space(result, i, 1);
	i = ft_strjoin_char(result, i, current->print_date, 13);
	i = ft_strjoin_space(result, i, 2);
	i = ft_strjoin_char(result, i, current->name, ft_strlen(current->name));
	result[++i]='\n';
	size = ft_strlen(result);
	write(1, result, size);
	write(1, "\n",1);
	free(result);
}

void	ft_print(t_curr *curr_dir, t_fl *fl)
	{
		t_count *count;
		t_curr 	*curr;
		int	i;
		char *print;

		curr = curr_dir;
		count = ft_count_s(curr_dir, fl->l);
		if (fl->l == 1)
		{
			write(1, "total ", 6);
			ft_putnbr(count->total);
			write(1, "\n", 1);
			while (curr)
			{
				ft_strprint_join(curr, 30 + count->s_links + count->s_user +
				count->s_groop + count->s_size + ft_strlen(curr->name) + 1,
				count);
				curr = curr->next;
			}
		}
		else
		{
			if (!(print = ft_strnew(count->s_name)))
				return ;
			i = 0;
			while(curr)
			{
				i = ft_strjoin_char(print, i, curr->name, ft_strlen(curr->name));
				print[i++] = '\n';
				//	write(1, (curr->name), ft_strlen(curr->name));
				//	write(1, "\n", 1);
				curr = curr->next;
			}
			print[i] = '\0';
			ft_putstr(print);
			free(print);
		}
		if (fl->l == 1)
			free(count);
}


