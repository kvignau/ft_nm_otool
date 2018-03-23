/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mask.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <kvignau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 18:01:28 by kvignau           #+#    #+#             */
/*   Updated: 2016/02/16 13:15:40 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_mask0(wchar_t nb)
{
	char		*str;

	str = ft_strnew(1);
	str[1] = '\0';
	str[0] = nb;
	return (str);
}

char		*ft_mask1(wchar_t nb)
{
	char			*str;
	unsigned int	a;
	unsigned int	b;

	str = ft_strnew(2);
	str[2] = '\0';
	a = 0x3F & nb;
	nb <<= 2;
	b = 0x1F00 & nb;
	b = b | a | 0xC080;
	str[1] = b;
	str[0] = b >> 8;
	return (str);
}

char		*ft_mask2(wchar_t nb)
{
	char			*str;
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;

	str = ft_strnew(3);
	str[3] = '\0';
	a = 0x3F & nb;
	nb <<= 2;
	b = 0x3F00 & nb;
	nb <<= 2;
	c = 0xF0000 & nb;
	b = b | a | c | 0xE08080;
	str[2] = b;
	str[1] = b >> 8;
	str[0] = b >> 16;
	return (str);
}

char		*ft_mask3(wchar_t nb)
{
	char			*str;
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;
	unsigned int	d;

	str = ft_strnew(4);
	str[4] = '\0';
	a = 0x3F & nb;
	nb <<= 2;
	b = 0x3F00 & nb;
	nb <<= 2;
	c = 0x3F0000 & nb;
	nb <<= 2;
	d = 0x7000000 & nb;
	b = b | a | c | d | 0xF0808080;
	str[3] = b;
	str[2] = b >> 8;
	str[1] = b >> 16;
	str[0] = b >> 24;
	return (str);
}
