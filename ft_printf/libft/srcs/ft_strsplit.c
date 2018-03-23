/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 16:13:48 by kvignau           #+#    #+#             */
/*   Updated: 2016/01/18 11:51:14 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_strlencar(char const *s, char c, int i)
{
	int		len;

	len = i;
	while (s[len] && s[len] != c)
		len++;
	return (len - i);
}

static char			*ft_stradd(char const *s, char c, int i)
{
	char			*word;
	int				len;
	int				j;

	j = 0;
	len = ft_strlencar(s, c, i);
	word = ft_strnew(len + 1);
	if (!word)
		return (NULL);
	while (s[i] && j < len)
	{
		word[j] = s[i + j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

char				**ft_strsplit(char const *s, char c)
{
	char			**tab;
	int				j;
	int				i;
	int				ok;

	ok = 1;
	i = 0;
	j = 0;
	tab = (char **)malloc(sizeof(char *) * (ft_nbwords(s, c) + 1));
	if (!tab || !s)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c && ok)
		{
			ok = 0;
			tab[j++] = ft_stradd(s, c, i);
		}
		else if (s[i] == c)
			ok = 1;
		i++;
	}
	tab[j] = 0;
	return (tab);
}
