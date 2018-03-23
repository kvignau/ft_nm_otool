/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 17:04:42 by kvignau           #+#    #+#             */
/*   Updated: 2015/12/01 13:32:44 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;

	i = 0;
	if (s && f)
	{
		str = ft_strnew(ft_strlen(s));
		if (!str)
			return (NULL);
		while (s[i])
		{
			str[i] = (*f)((unsigned int)i, s[i]);
			i++;
		}
		return (str);
	}
	else
		return (NULL);
}
