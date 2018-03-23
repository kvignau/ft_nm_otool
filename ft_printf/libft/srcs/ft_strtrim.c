/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 12:09:55 by kvignau           #+#    #+#             */
/*   Updated: 2016/01/18 10:54:26 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	len;
	char	*str;

	i = 0;
	if (s == NULL)
		return (NULL);
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && s[i])
		i++;
	len = ft_strlen(s + i) - 1;
	while ((s[len + i] == ' ' || s[len + i] == '\n' ||
				s[len + i] == '\t') && s[i])
		len--;
	str = ft_strnew(len + 1);
	if (!str)
		return (NULL);
	ft_strncpy(str, s + i, len + 1);
	return (str);
}
