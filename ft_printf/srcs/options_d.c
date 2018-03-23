/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <kvignau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 16:39:49 by kvignau           #+#    #+#             */
/*   Updated: 2016/02/22 16:58:51 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_cast_d(void *arg, t_modifier modifier)
{
	if (modifier.hh)
		return (ft_itoa_base_imax((signed char)arg, 10));
	else if (modifier.h)
		return (ft_itoa_base_imax((short)arg, 10));
	else if (modifier.ll)
		return (ft_itoa_base_imax((long long)arg, 10));
	else if (modifier.l)
		return (ft_itoa_base_imax((long)arg, 10));
	else if (modifier.j)
		return (ft_itoa_base_imax((intmax_t)arg, 10));
	else if (modifier.z)
		return (ft_itoa_base_imax((ssize_t)arg, 10));
	else
		return (ft_itoa_base_imax((int)arg, 10));
}

char		*ft_precision_d(char *str, t_options options, size_t len)
{
	int		len_p;
	int		len_w;
	char	*recup;

	recup = NULL;
	len_w = options.flags.width - len;
	len_p = options.precision - len;
	if (len_w <= 0 && len_p <= 0)
		return (str);
	if (options.specifier == 'd' && (options.flags.plus ||
		ft_strchr(str, '-')))
		len_p++;
	if (len_p < 0)
		len_p = 0;
	if (options.flags.moins)
		str = ft_minus_p(len_p, len_w, options, str);
	else if (len_w >= len_p)
		str = ft_zero_p(len_p, len_w, options, str);
	else
	{
		recup = ft_putzero_d(len_p, str);
		str = ft_strjoinandfree(recup, str, 3);
	}
	return (str);
}

char		*ft_putspace_d(int len)
{
	char	*space;
	int		i;

	i = 0;
	if (len <= 0)
		return (NULL);
	space = ft_strnew(len);
	while (i < len)
	{
		space[i] = ' ';
		i++;
	}
	space[i] = '\0';
	return (space);
}

char		*ft_putzero_d(int len, char *s)
{
	char	c;

	c = ' ';
	if (len <= 0)
		return (NULL);
	if (s)
	{
		if (s[0] == '-' || s[0] == '+')
		{
			c = s[0];
			s[0] = '0';
		}
	}
	return (ft_sign_d(c, len));
}

char		*ft_sign_d(char c, int len)
{
	char	*zero;
	int		i;

	i = 0;
	zero = ft_strnew(len);
	if (c != ' ')
	{
		zero[i] = c;
		i++;
	}
	while (i < len)
	{
		zero[i] = '0';
		i++;
	}
	zero[i] = '\0';
	return (zero);
}
