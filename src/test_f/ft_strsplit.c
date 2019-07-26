/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 19:37:02 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/04/18 16:02:03 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_memdl(void **ap);
char	*ft_strnew(int size);

static int		sl(const char *s, char c, int a)
{
	int i;
	int r;

	r = 0;
	i = -1;
	if (a == 0)
	{
		while (s[++i])
			while (s[i] != c && s[i++])
				if (s[i] == c || s[i] == '\0')
					r++;
	}
	else
		while (s[++i])
			while (s[i] != c && s[i++])
			{
				r++;
				if (s[i] == c || s[i] == '\0')
					return (r);
			}
	return (r);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**b;
	int	i;
	int	j;
	int	k;

	if (!s || !(b = (char**)malloc(sizeof(char*) * (sl(s, c, 0) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			k = 0;
			if (!(b[j] = ft_strnew(sl(s + i, c, 1))) && !ft_memdl((void **)b))
				return (NULL);
			while (s[i] && s[i] != c)
				b[j][k++] = s[i++];
			j++;
		}
		else
			i++;
	}
	b[j] = NULL;
	return (b);
}
