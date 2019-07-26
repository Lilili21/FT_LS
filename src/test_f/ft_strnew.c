/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 17:41:21 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/04/18 20:16:57 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *b, int c, int len);

char	*ft_strnew(int size)
{
	char *n;

	if (size + 1 == 0)
		return (NULL);
	if (!(n = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_memset(n, 0, size + 1);
	return (n);
}
