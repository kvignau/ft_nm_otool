/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 15:22:13 by kvignau           #+#    #+#             */
/*   Updated: 2015/11/25 16:28:34 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	void			*tmp;

	tmp = (void *)malloc(sizeof(void) * len);
	ft_memcpy(tmp, src, len);
	ft_memcpy(dst, tmp, len);
	ft_memdel((void **)&tmp);
	return (dst);
}
