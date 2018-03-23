/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 11:52:17 by kvignau           #+#    #+#             */
/*   Updated: 2016/01/27 11:31:35 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char						*ft_itoa(int n)
{
	int			i;
	int			j;
	int			len;
	char		*str;
	char		*itoa;

	len = ft_nbrlen(n, 10);
	i = 0;
	j = 0;
	str = ft_strnew(len);
	if (!str)
		return (NULL);
	if (n < 0)
		str[i++] = '-';
	itoa = ft_itoa_base(n, 10);
	while (itoa[j] != '\0')
	{
		str[i + j] = itoa[j];
		j++;
	}
	str[i + j] = '\0';
	ft_memdel((void **)&itoa);
	return (str);
}
