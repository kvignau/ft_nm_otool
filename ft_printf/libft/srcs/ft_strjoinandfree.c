/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinandfree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 19:19:38 by kvignau           #+#    #+#             */
/*   Updated: 2016/03/23 19:19:42 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoinandfree(char const *s1, char const *s2, int i)
{
	char	*join;
	size_t	len;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (!s1)
		return ((char *)s2);
	else if (!s2)
		return ((char *)s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	join = ft_strnew(len);
	if (!join)
		return (NULL);
	if (s1)
		ft_strcpy(join, s1);
	if (s2)
		ft_strcat(join, s2);
	if (i == 1 || i == 3)
		free((char *)s1);
	if (i == 2 || i == 3)
		free((char *)s2);
	return (join);
}
