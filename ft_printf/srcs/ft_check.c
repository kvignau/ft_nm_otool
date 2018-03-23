/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 10:22:35 by kvignau           #+#    #+#             */
/*   Updated: 2016/01/28 14:03:18 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_init_options(t_options *options)
{
	options->flags.width = 0;
	options->flags.zero = 0;
	options->flags.moins = 0;
	options->flags.plus = 0;
	options->flags.space = 0;
	options->flags.hashtag = 0;
	options->modifier.hh = 0;
	options->modifier.h = 0;
	options->modifier.ll = 0;
	options->modifier.l = 0;
	options->modifier.j = 0;
	options->modifier.z = 0;
	options->precision = -1;
	options->specifier = '\0';
}

int			get_flags(char const flag, t_options *options)
{
	if (ft_strchr(FLAGS, flag))
	{
		ft_putflag(flag, options);
		return (1);
	}
	return (0);
}

void		ft_putflag(char const flag, t_options *options)
{
	if (flag == '#')
		options->flags.hashtag = 1;
	else if (flag == ' ')
		options->flags.space = 1;
	else if (flag == '+')
		options->flags.plus = 1;
	else if (flag == '-')
		options->flags.moins = 1;
	else if (flag == '0')
		options->flags.zero = 1;
}

int			get_modifier(char const *format, t_options *options, int x)
{
	if (format[x] == 'h')
	{
		options->modifier.h += 1;
		return (1);
	}
	else if (format[x] == 'l')
	{
		options->modifier.l += 1;
		return (1);
	}
	else if (format[x] == 'j')
	{
		options->modifier.j = 1;
		return (1);
	}
	else if (format[x] == 'z')
	{
		options->modifier.z = 1;
		return (1);
	}
	return (0);
}

int			get_specifiers(char const specifier, t_options *options)
{
	int		i;

	i = 0;
	while (SPECIFIERS[i])
	{
		if (specifier == SPECIFIERS[i])
		{
			options->specifier = SPECIFIERS[i];
			return (i);
		}
		i++;
	}
	options->specifier = specifier;
	return (-1);
}
