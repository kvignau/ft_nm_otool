/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:24:45 by kvignau           #+#    #+#             */
/*   Updated: 2015/12/01 13:29:05 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_bzero(void *s, size_t len)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	if (len == 0)
		return (s);
	str = (unsigned char *)s;
	while (i < len)
	{
		str[i] = 0;
		i++;
	}
	return (s);
}
