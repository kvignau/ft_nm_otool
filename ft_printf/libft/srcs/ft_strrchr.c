/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 13:32:09 by kvignau           #+#    #+#             */
/*   Updated: 2015/11/26 11:05:17 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	int		i;

	i = ft_strlen(s);
	if (c == '\0')
		return ((char *)&s[i]);
	while (i >= 0 && s[i] != c)
		i--;
	if (i >= 0)
		return ((char *)&s[i]);
	return (NULL);
}
