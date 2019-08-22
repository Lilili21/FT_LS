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
