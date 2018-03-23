/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_wchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <kvignau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 14:10:59 by kvignau           #+#    #+#             */
/*   Updated: 2016/02/16 13:16:44 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_getmask(wchar_t nb)
{
	if (nb <= 127)
		return (ft_mask0(nb));
	else if (nb <= 2047)
		return (ft_mask1(nb));
	else if (nb <= 65535)
		return (ft_mask2(nb));
	else
		return (ft_mask3(nb));
}

char		*ft_getmask_prec(wchar_t nb, int *prec)
{
	char	*str;

	if (nb <= 127)
		str = ft_mask0(nb);
	else if (nb <= 2047)
	{
		(*prec)--;
		str = ft_mask1(nb);
	}
	else if (nb <= 65535)
	{
		(*prec) = (*prec) - 2;
		str = ft_mask2(nb);
	}
	else
	{
		(*prec) = (*prec) - 3;
		str = ft_mask3(nb);
	}
	(*prec)--;
	if ((*prec) >= 0)
		return (str);
	free(str);
	return (NULL);
}

char		*ft_wchar(t_options *options, wchar_t *wstr)
{
	size_t	len;
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	len = 0;
	if (options->precision >= 0)
		str = ft_prec_wchar(options, wstr);
	else
	{
		while (wstr[i])
			str = ft_strjoinandfree(str, ft_getmask(wstr[i++]), 3);
		if (str)
			len = ft_strlen(str);
		str = ft_flagspacezero_d(*options, len, str);
	}
	return (str);
}

char		*ft_prec_wchar(t_options *options, wchar_t *wstr)
{
	char	*str;
	int		prec;
	size_t	len;
	int		i;

	i = 0;
	str = NULL;
	len = 0;
	prec = options->precision;
	while (wstr[i] && prec >= 0)
		str = ft_strjoinandfree(str, ft_getmask_prec(wstr[i++], &prec), 3);
	if (str)
		len = ft_strlen(str);
	if (options->flags.moins)
		str = ft_strjoinandfree(str, ft_precision_wchar(*options, len), 3);
	else
		str = ft_strjoinandfree(ft_precision_wchar(*options, len), str, 3);
	return (str);
}

char		*ft_precision_wchar(t_options options, size_t len)
{
	int		len_w;
	char	*space;
	char	c;
	int		i;

	i = 0;
	c = ' ';
	len_w = options.flags.width - len;
	space = ft_strnew(len_w);
	if (options.flags.zero)
		c = '0';
	while (i < len_w)
	{
		space[i] = c;
		i++;
	}
	return (space);
}
