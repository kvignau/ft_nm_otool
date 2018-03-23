/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <kvignau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 10:22:18 by kvignau           #+#    #+#             */
/*   Updated: 2016/02/16 18:44:03 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_specerror(char c, t_options *options)
{
	char		*str;

	str = ft_strnew(1);
	str[0] = c;
	str[1] = '\0';
	if (!(options->flags.width) && !(options->flags.zero)
		&& !(options->flags.moins) && !(options->flags.plus) &&
		!(options->flags.space) && !(options->flags.hashtag) &&
		options->precision == -1 && ft_isalpha(options->specifier))
		return (NULL);
	if (options->precision >= 0)
		str = ft_flagspacezero_c(*options, 1, str);
	else
		str = ft_flagspacezero_d(*options, 1, str);
	return (str);
}

char		*ft_char(void *arg, t_options *options)
{
	char		*str;
	int			len;

	str = NULL;
	len = 1;
	if (options->modifier.l == 1)
		str = ft_getmask((wchar_t)arg);
	else if (options->specifier == '%')
		str = ft_strdup("%");
	else
		str = ft_cast_c(arg, options->modifier);
	if (str)
		len = ft_strlen(str);
	str = ft_flagspacezero_c(*options, len, str);
	return (str);
}

char		*ft_string(void *arg, t_options *options)
{
	char	*str;
	wchar_t	*wstr;
	size_t	len;

	str = NULL;
	len = 0;
	if (arg == NULL && options->precision >= 0)
		return (ft_precision_s(str, *options, 0));
	else if (arg == NULL && options->flags.width)
		return (ft_flagspacezero_d(*options, 0, str));
	else if (arg == NULL)
		return (ft_strdup("(null)"));
	if (options->modifier.l == 1)
	{
		wstr = (wchar_t *)arg;
		str = ft_wchar(options, wstr);
	}
	else
	{
		str = ft_strdup((char *)arg);
		str = ft_str(options, str);
	}
	return (str);
}

char		*ft_str(t_options *options, char *str)
{
	size_t	len;

	len = 0;
	if (str)
		len = ft_strlen(str);
	if (options->precision >= 0)
		str = ft_precision_s(str, *options, len);
	else
		str = ft_flagspacezero_d(*options, len, str);
	return (str);
}

char		*ft_pointer(void *arg, t_options *options)
{
	size_t	len;
	char	*str;

	str = NULL;
	len = 0;
	if (arg != NULL)
	{
		str = ft_itoa_base_uimax((uintmax_t)arg, 16);
		len = ft_strlen(str);
	}
	if (options->flags.hashtag == 1 && options->precision == -1)
		str = ft_point_0x(&len, str);
	else if (options->flags.hashtag == 1)
	{
		if (str)
			str = ft_strjoinandfree("0x", str, 2);
		else
			str = ft_strdup("0x");
	}
	if (options->precision >= 0)
		str = ft_precision_p(str, *options, len);
	else
		str = ft_flagspacezero_x(*options, len, str);
	return (str);
}
