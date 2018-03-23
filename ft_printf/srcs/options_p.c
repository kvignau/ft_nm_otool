/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <kvignau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 13:15:10 by kvignau           #+#    #+#             */
/*   Updated: 2016/02/16 18:37:18 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_precision_p(char *str, t_options options, size_t len)
{
	int		len_p;
	int		len_w;
	char	*recup;

	len_w = options.flags.width - len;
	len_p = options.precision - len;
	if (len_p < 0)
		len_p = 0;
	if (len_w < 0 && len_p < 0)
		return (str);
	if (options.flags.moins)
		str = ft_minus_p(len_p, len_w, options, str);
	else if (len_w >= len_p)
	{
		len_w -= 2;
		str = ft_zero_p(len_p, len_w, options, str);
	}
	else
	{
		recup = ft_putzero_x(len_p, options.flags.hashtag, str);
		str = ft_strjoinandfree(recup, str, 3);
	}
	return (str);
}

char		*ft_zero_p(int len_p, int len_w, t_options options, char *str)
{
	char	*recup;

	if (options.flags.zero && options.specifier != 'd')
		recup = ft_putspace_d(len_w - len_p);
	else
	{
		if (options.specifier == 'd')
			recup = ft_strjoinandfree(ft_putspace_d(len_w - len_p),
				ft_putzero_d(len_p, str), 3);
		else
			recup = ft_strjoinandfree(ft_putspace_d(len_w - len_p),
				ft_putzero_x(len_p, options.flags.hashtag, str), 3);
	}
	str = ft_strjoinandfree(recup, str, 3);
	return (str);
}

char		*ft_minus_p(int len_p, int len_w, t_options options, char *str)
{
	char	*recup;

	recup = NULL;
	if (options.specifier == 'p' || options.specifier == 'x')
		recup = ft_putzero_x(len_p, options.flags.hashtag, str);
	else
		recup = ft_putzero_d(len_p, str);
	if (recup)
		str = ft_strjoinandfree(recup, str, 3);
	if (options.flags.width > options.precision)
	{
		recup = ft_putspace_d(len_w - len_p);
		if (recup)
			str = ft_strjoinandfree(str, recup, 3);
	}
	return (str);
}

char		*ft_point_0x(size_t *len, char *str)
{
	if (*len == 0)
	{
		str = ft_strdup("0x0");
		(*len) += 3;
	}
	else
	{
		str = ft_strjoinandfree("0x", str, 2);
		(*len) += 2;
	}
	return (str);
}
