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


int 	ft_strjoin_space(char *result, int i, int space_number)
{
	int j;

	j = -1;
	while(++j < space_number)
		result[i++] = ' ';
	return (i);
}

int		ft_strjoin_char(char *result, int i, char *src, size_t m_size)
{
	int j;
	size_t src_size;

	j = -1;
	src_size = ft_strlen(src);
	if (src_size < m_size)
		i = ft_strjoin_space(result, i, m_size-src_size);
	while(++j < src_size)
		result[++i] = src[j];
	return (i);
}

void 	ft_strprint_join(t_curr *current, int size, t_count *count_col)
{
	char *result;
	int i;

	i = 0;
	if (!(result = ft_strnew(size)))
		return ;
	i = ft_strjoin_char(result, i, current->rights, 10);
	i = ft_strjoin_space(result, i, 3);
	i = ft_strjoin_char(result, i, ft_itoa(current->links), count_col->s_links);
	i = ft_strjoin_space(result, i, 3);
	i = ft_strjoin_char(result, i, current->user, count_col->s_user);
	i = ft_strjoin_space(result, i, 3);
	i = ft_strjoin_char(result, i, current->groop, count_col->s_groop);
	i = ft_strjoin_space(result, i, 3);
	i = ft_strjoin_char(result, i,  ft_itoa(current->size), count_col->s_size);
	i = ft_strjoin_space(result, i, 3);
	i = ft_strjoin_char(result, i, current->print_date, 13);
	i = ft_strjoin_space(result, i, 3);
	i = ft_strjoin_char(result, i, current->name, ft_strlen(current->name));
	result[++i]='\n';
	write(1, &result, size);
	free(result);
}

void ft_print(t_curr *curr_dir, t_fl *fl)
	{
		t_count *count;
		t_curr 	*curr;
		int		size;

		if (fl->l == 1)
			count = ft_count_s(curr_dir);
		curr = curr_dir;
		while (curr)
		{	if (fl->l == 1)
			{
				size = 30 + count->s_links + count->s_user + count->s_groop
					   + count->s_size + ft_strlen(curr->name) + 1; //учтен \n
				ft_strprint_join(curr, size, count);
			}
			else
			{
				if (!(size = ft_strlen(curr->name)))
					return ;
				write(1, curr->name,ft_strlen(curr->name));
				write(1, "\n", 1);
			}
			curr = curr->next;
		}
		if (fl->l == 1)
			free(count);
}
