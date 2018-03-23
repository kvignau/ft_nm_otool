/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 10:28:13 by kvignau           #+#    #+#             */
/*   Updated: 2015/11/26 10:03:43 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(s1);
	len = ft_strlen(s2);
	if (s2[i] == '\0')
		return ((char *)s1);
	if (n >= len)
	{
		while (s1[i] && i < n)
		{
			while (s1[i + j] == s2[j] && s2[j] && (i + j) < n)
				j++;
			if (j == len)
				return ((char *)&s1[i]);
			i++;
			j = 0;
		}
	}
	return (NULL);
}
