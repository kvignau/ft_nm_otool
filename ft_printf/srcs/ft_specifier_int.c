/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <kvignau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 10:22:25 by kvignau           #+#    #+#             */
/*   Updated: 2016/02/16 17:53:32 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_hexalower(void *arg, t_options *options)
{
	size_t	len;
	char	*str;

	str = NULL;
	len = 0;
	if (!(arg == 0 && options->precision == 0))
	{
		str = ft_cast_ui(arg, options->modifier, 16);
		len = ft_strlen(str);
		if (options->flags.hashtag == 1 &&
			(options->precision <= options->flags.width ||
			options->precision == -1))
		{
			str = ft_flaghashtag(arg, *options, str);
			len += 2;
		}
		else if (options->flags.hashtag == 1)
			str = ft_flaghashtag(arg, *options, str);
	}
	if (options->precision >= 0)
		str = ft_precision_x(str, *options, len);
	else
		str = ft_flagspacezero_x(*options, len, str);
	return (str);
}

char		*ft_hexaupper(void *arg, t_options *options)
{
	return (ft_strupper(ft_hexalower(arg, options)));
}

char		*ft_octal(void *arg, t_options *options)
{
	size_t	len;
	char	*str;

	str = NULL;
	len = 0;
	if (options->flags.hashtag == 1 ||
		!(arg == 0 && options->precision == 0))
	{
		str = ft_cast_ui(arg, options->modifier, 8);
		if (options->flags.hashtag == 1)
			str = ft_flaghashtag(arg, *options, str);
		len = ft_strlen(str);
	}
	if (options->precision >= 0)
		str = ft_precision_d(str, *options, len);
	else
		str = ft_flagspacezero_d(*options, len, str);
	return (str);
}

char		*ft_dec(void *arg, t_options *options)
{
	char		*str;
	size_t		len;
	char		*tmp;

	str = NULL;
	tmp = NULL;
	len = 0;
	if (!(arg == 0 && options->precision == 0))
	{
		str = ft_cast_d(arg, options->modifier);
		tmp = ft_strchr(str, '-');
		if (options->flags.plus && !tmp)
		{
			str = ft_strjoinandfree("+", str, 2);
			free(tmp);
		}
		len = ft_strlen(str);
	}
	if (options->precision >= 0)
		str = ft_precision_d(str, *options, len);
	else
		str = ft_flagspacezero_d(*options, len, str);
	return (str);
}

char		*ft_usi(void *arg, t_options *options)
{
	char		*str;
	size_t		len;

	str = NULL;
	len = 0;
	if (!(arg == 0 && options->precision == 0))
	{
		str = ft_cast_ui(arg, options->modifier, 10);
		len = ft_strlen(str);
	}
	if (options->precision > 0)
		str = ft_precision_d(str, *options, len);
	else
		str = ft_flagspacezero_d(*options, len, str);
	return (str);
}
