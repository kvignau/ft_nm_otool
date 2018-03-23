/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <kvignau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 18:03:03 by kvignau           #+#    #+#             */
/*   Updated: 2016/02/12 17:25:35 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_precision_s(char *str, t_options options, size_t len)
{
	int		len_w;
	char	*recup;

	if (options.precision < (int)len)
		str[options.precision] = '\0';
	if (str)
		len = ft_strlen(str);
	len_w = options.flags.width - len;
	if (len_w < 0)
		return (str);
	if (options.flags.moins)
		str = ft_minus_s(options, len_w, str);
	else
	{
		if (options.flags.zero)
			recup = ft_putzero_d(len_w, str);
		else
			recup = ft_putspace_d(len_w);
		if (recup)
			str = ft_strjoinandfree(recup, str, 3);
	}
	return (str);
}

char		*ft_minus_s(t_options options, int len_w, char *str)
{
	char	*recup;

	recup = NULL;
	if (options.flags.width > options.precision)
	{
		recup = ft_putspace_d(len_w);
		if (recup)
			str = ft_strjoinandfree(str, recup, 3);
	}
	return (str);
}
