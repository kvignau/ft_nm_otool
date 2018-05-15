/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 20:07:28 by kvignau           #+#    #+#             */
/*   Updated: 2018/05/14 20:07:31 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int					ft_errors(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (EXIT_FAILURE);
}

uint32_t			reverse_endian(uint32_t narch)
{
	narch = ((narch << 8) & 0xFF00FF00) | ((narch >> 8) & 0xFF00FF);
	return (narch << 16) | (narch >> 16);
}

int					check_corrupt(void *ptr, void *buf)
{
	if (ptr > buf)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void				ft_add_precision(uintmax_t value, int is64bit)
{
	char			*str;
	char			*res;
	int				system_type;
	int				i;
	int				len;

	i = 0;
	str = ft_itoa_base_uimax(value, 16);
	len = ft_strlen(str);
	system_type = is64bit == 1 ? 16 : 8;
	res = (char *)malloc(sizeof(char) * (system_type + 1));
	res[system_type] = '\0';
	while (i < system_type - len)
		res[i++] = '0';
	while (i < system_type)
	{
		res[i] = str[i - (system_type - len)];
		i++;
	}
	free(str);
	ft_putstr(res);
	free(res);
}

void				print_byte_to_hex(char byte, int env, uintmax_t x)
{
	char			str[2];
	short			count;
	short			char_hex;
	unsigned char	cast;

	cast = (unsigned char)byte;
	count = -1;
	while (++count != 2)
	{
		char_hex = cast % 16;
		cast /= 16;
		if (char_hex < 10)
			str[count] = char_hex + '0';
		else
			str[count] = (char_hex % 10) + 'a';
	}
	ft_putchar(str[1]);
	ft_putchar(str[0]);
	if (env > 3)
	{
		if (x % 4 == 0)
			ft_putchar(' ');
	}
	else
		ft_putchar(' ');
}
