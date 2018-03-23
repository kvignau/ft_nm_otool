/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <kvignau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 15:47:44 by kvignau           #+#    #+#             */
/*   Updated: 2016/03/03 13:19:52 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf(const char *restrict format, ...)
{
	int			i;
	int			cpt;
	va_list		arg;
	t_options	options;

	i = 0;
	cpt = 0;
	va_start(arg, format);
	while (format && format[i])
	{
		if (format[i] == '{')
		{
			i++;
			ft_color(format, &i);
		}
		if (format[i] == '%')
			cpt += ft_percent(format, &i, &options, arg);
		else
			cpt += write(1, &(format[i]), 1);
		i++;
	}
	va_end(arg);
	return (cpt);
}

int				ft_percent(const char *restrict format, int *i,
	t_options *options, va_list arg)
{
	int			cpt;
	int			ret;
	char		*str;

	cpt = 0;
	ret = 0;
	str = NULL;
	(*i)++;
	if (!format[*i])
		return (0);
	ft_init_options(options);
	if ((ret = split_options(format, i, options)) == -1)
	{
		str = ft_specerror(options->specifier, options);
		if (str != NULL)
		{
			cpt = write(1, str, ft_strlen(str));
			free(str);
		}
		return (cpt);
	}
	else
		return (ft_percent_suite(options, arg, ret, cpt));
}

int				ft_percent_suite(t_options *options, va_list arg, int ret,
	int cpt)
{
	char		*str;

	str = NULL;
	ft_test_flags(options);
	if (options->specifier == '%')
	{
		str = ft_char("%", options);
		if (str != NULL)
			cpt = write(1, str, ft_strlen(str));
		str != NULL ? free(str) : NULL;
		return (cpt);
	}
	else
	{
		str = ft_action(arg, options, ret);
		if (str != NULL)
			return (ft_specifier_no_null(options, str));
		else
		{
			if (options->flags.width == 0 && options->specifier == 'c')
				return (1);
			else
				return (options->flags.width);
		}
	}
}

int				ft_specifier_no_null(t_options *options, char *str)
{
	int			cpt;

	cpt = 0;
	if (options->specifier == 'c' && options->flags.width != 0)
		cpt = write(1, str, options->flags.width);
	else if (options->specifier == 'c' && str[0] == '\0')
		cpt = write(1, str, 1);
	else
		cpt = write(1, str, ft_strlen(str));
	free(str);
	return (cpt);
}

void			ft_splitmod(t_options *options)
{
	if (options->modifier.h > 0)
	{
		if (options->modifier.h % 2 == 0)
		{
			options->modifier.h = 0;
			options->modifier.hh = 1;
		}
		else
			options->modifier.h = 1;
	}
	else if (options->modifier.l > 0)
	{
		if (options->modifier.l % 2 == 0)
		{
			options->modifier.l = 0;
			options->modifier.ll = 1;
		}
		else
			options->modifier.l = 1;
	}
}
