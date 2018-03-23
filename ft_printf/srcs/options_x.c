/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <kvignau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 18:06:06 by kvignau           #+#    #+#             */
/*   Updated: 2016/02/16 18:41:51 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_precision_x(char *str, t_options options, size_t len)
{
	int		len_p;
	int		len_w;
	char	*recup;

	len_w = options.flags.width - len;
	len_p = options.precision - len;
	if (len_w <= 0 && len_p <= 0)
		return (str);
	if (len_p < 0)
		len_p = 0;
	if (options.flags.moins)
		str = ft_minus_p(len_p, len_w, options, str);
	else if (len_w >= len_p)
		str = ft_zero_p(len_p, len_w, options, str);
	else
	{
		recup = ft_putzero_x(len_p, options.flags.hashtag, str);
		str = ft_strjoinandfree(recup, str, 3);
	}
	return (str);
}

char		*ft_flagspacezero_x(t_options options, size_t len, char *str)
{
	char	*recup;
	int		ret;
	size_t	i;

	i = 0;
	ret = options.flags.width - len;
	if (ret > 0)
	{
		recup = ft_strnew(ret);
		if (options.flags.moins)
			str = ft_strjoinandfree(str, ft_putspace_d(ret), 3);
		else
		{
			if (options.flags.zero == 1 && options.flags.space == 1)
				recup = ft_strjoinandfree(ft_putspace_d(1),\
					ft_putzero_x(ret, options.flags.hashtag, str), 3);
			else if (options.flags.zero == 1)
				recup = ft_putzero_x(ret, options.flags.hashtag, str);
			else if (options.flags.space == 1 || options.flags.width != 0)
				recup = ft_putspace_d(ret);
			str = ft_strjoinandfree(recup, str, 3);
		}
	}
	return (str);
}

char		*ft_putzero_x(int len, int hashtag, char *s)
{
	char	*zero;
	int		i;

	i = 0;
	if (len <= 0)
		return (NULL);
	zero = ft_strnew(len);
	if (hashtag)
	{
		while (i < 2)
		{
			zero[i] = s[i];
			s[i++] = '0';
		}
	}
	while (i < len)
	{
		zero[i] = '0';
		i++;
	}
	zero[i] = '\0';
	return (zero);
}
