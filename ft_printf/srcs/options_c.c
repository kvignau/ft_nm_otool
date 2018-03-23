/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <kvignau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 14:44:59 by kvignau           #+#    #+#             */
/*   Updated: 2016/02/15 17:24:48 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_cast_c(void *arg, t_modifier modifier)
{
	char	*str;

	if (arg == NULL)
		return (NULL);
	modifier.l = 0;
	str = ft_strnew(1);
	str[0] = (int)arg;
	str[1] = '\0';
	return (str);
}

char		*ft_flagspacezero_c(t_options options, size_t len, char *str)
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
		{
			str = ft_strjoinandfree(str, ft_putspace_d(ret), 3);
		}
		else
		{
			if (options.flags.zero == 1)
				recup = ft_putzero_c(ret);
			else if (options.flags.space == 1 || options.flags.width != 0)
				recup = ft_putspace_d(ret);
			str = ft_strjoinandfree(recup, str, 3);
		}
	}
	return (str);
}

char		*ft_putzero_c(int len)
{
	char	*zero;
	int		i;

	i = 0;
	if (len <= 0)
		return (NULL);
	zero = ft_strnew(len);
	while (i < len)
	{
		zero[i] = '0';
		i++;
	}
	zero[i] = '\0';
	return (zero);
}
