/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 13:23:05 by kvignau           #+#    #+#             */
/*   Updated: 2016/01/18 11:24:33 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const unsigned char		*src1;
	unsigned char			*dst1;
	unsigned char			c1;
	size_t					i;

	i = 0;
	src1 = (unsigned char *)src;
	dst1 = (unsigned char *)dst;
	c1 = (unsigned char)c;
	while (i < n && c1 != src1[i])
	{
		dst1[i] = src1[i];
		i++;
	}
	if (n == i)
		return (NULL);
	if (src1[i] == c1)
	{
		dst1[i] = src1[i];
		i++;
	}
	return ((void *)&dst1[i]);
}
