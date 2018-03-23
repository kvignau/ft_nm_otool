/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 16:36:32 by kvignau           #+#    #+#             */
/*   Updated: 2016/02/10 14:50:07 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			split_options(char const *format, int *x,
		t_options *options)
{
	int						ret;

	ret = 0;
	while (get_flags(format[*x], options))
		*x = (*x) + 1;
	options->flags.width = ft_atoi(format + *x);
	while (format[*x] >= '0' && format[*x] <= '9')
		(*x)++;
	if (format[*x] == '.')
	{
		*x = *x + 1;
		options->precision = ft_atoi(format + *x);
	}
	while (format[*x] >= '0' && format[*x] <= '9')
		(*x)++;
	while (get_modifier(format, options, *x))
		*x = (*x) + 1;
	ft_splitmod(options);
	if ((ret = get_specifiers(format[*x], options)) != -1)
		return (ret);
	return (-1);
}

char		*ft_action(va_list arguments, t_options *options, int ret)
{
	void						*arg;
	static const t_affiche		functions[] = {ft_string, ft_dec, ft_dec,
		ft_octal, ft_char, ft_pointer, ft_hexalower, ft_hexaupper, ft_dec,
		ft_octal, ft_usi, ft_usi, ft_char, ft_string, ft_bin};
	t_affiche					test;

	arg = va_arg(arguments, void *);
	test = functions[ret];
	return (test(arg, options));
}

void		ft_test_flags(t_options *options)
{
	if (options->flags.zero == 1 && options->flags.moins == 1)
		options->flags.zero = 0;
	if (options->flags.space == 1 && options->flags.moins == 1)
		options->flags.space = 0;
	if (options->specifier == 'i')
		options->specifier = 'd';
	if (options->specifier == 'C')
		ft_longspecifier(options);
	if (options->specifier == 'S')
		ft_longspecifier(options);
	if (options->specifier == 'p')
	{
		options->specifier = 'x';
		options->flags.hashtag = 1;
	}
	if (options->specifier == 'D' || options->specifier == 'O'
	|| options->specifier == 'U')
		ft_longspecifier(options);
	if (options->precision > 0 && (options->specifier != 'c'
		&& options->specifier != 'x' && options->specifier != 'X'
		&& options->specifier != 's'))
		options->flags.zero = 0;
	if (options->flags.plus == 1 && options->flags.space == 1)
		options->flags.space = 0;
}

void		ft_longspecifier(t_options *options)
{
	options->modifier.hh = 0;
	options->modifier.h = 0;
	options->modifier.ll = 0;
	options->modifier.l = 1;
	options->modifier.j = 0;
	options->modifier.z = 0;
	options->specifier = ft_tolower(options->specifier);
}

char		*ft_flaghashtag(void *arg, t_options options, char *str)
{
	if ((int)arg != 0)
	{
		if (options.specifier == 'o')
			str = ft_strjoinandfree("0", str, 2);
		else if (options.specifier == 'x')
			str = ft_strjoinandfree("0x", str, 2);
		else if (options.specifier == 'X')
			str = ft_strjoinandfree("0X", str, 2);
	}
	return (str);
}
