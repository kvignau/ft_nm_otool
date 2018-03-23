/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 13:53:44 by kvignau           #+#    #+#             */
/*   Updated: 2015/11/30 17:59:23 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	lendst;
	size_t	lensrc;

	i = 0;
	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	if (size < lendst)
		return (size + lensrc);
	while (src[i] != '\0' && i < (size - lendst - 1))
	{
		dst[i + lendst] = src[i];
		i++;
	}
	dst[i + lendst] = '\0';
	return (lensrc + lendst);
}
