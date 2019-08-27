/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_print3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 18:46:59 by gfoote            #+#    #+#             */
/*   Updated: 2019/08/22 18:47:01 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsft.h"

int		ft_strjoin_char_0(char *result, int i, char *src, int m_size)
{
	int j;
	int src_size;

	if (!src && !m_size)
		return (i);
	j = 0;
	src_size = ft_strlen(src);
	if (src_size < m_size + 1)
		i = ft_strjoin_space(result, i, m_size - src_size);
	else
		i--;
	if (src)
		while (j < src_size + 1)
			result[++i] = src[j++];
	return (i);
}

int		ft_strjoin_char_1(char *result, int i, char *src, int m_size)
{
	int j;
	int src_size;

	if (!src && !m_size)
		return (i);
	j = 0;
	src_size = ft_strlen(src);
	i--;
	if (src)
		while (j < src_size + 1)
			result[++i] = src[j++];
	return (i);
}

int		ft_strjoin_char_2(char *result, int i, char *src, int m_size)
{
	int j;
	int src_size;

	if (!src && !m_size)
		return (i);
	j = 0;
	src_size = ft_strlen(src);
	i--;
	if (src)
		while (j < src_size + 1)
			result[++i] = src[j++];
	if (src_size < m_size + 1)
		i = ft_strjoin_space(result, i, m_size - src_size + 1);
	return (i);
}

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
