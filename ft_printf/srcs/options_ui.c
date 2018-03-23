/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_ui.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <kvignau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 16:56:57 by kvignau           #+#    #+#             */
/*   Updated: 2016/02/16 16:07:52 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_cast_ui(void *arg, t_modifier modifier, size_t base)
{
	if (modifier.hh)
		return (ft_itoa_base_uimax((unsigned char)arg, base));
	else if (modifier.h)
		return (ft_itoa_base_uimax((unsigned short)arg, base));
	else if (modifier.ll)
		return (ft_itoa_base_uimax((unsigned long long)arg, base));
	else if (modifier.l)
		return (ft_itoa_base_uimax((unsigned long)arg, base));
	else if (modifier.j)
		return (ft_itoa_base_uimax((uintmax_t)arg, base));
	else if (modifier.z)
		return (ft_itoa_base_uimax((size_t)arg, base));
	else
		return (ft_itoa_base_uimax((unsigned int)arg, base));
}

char		*ft_flagspacezero_d(t_options options, size_t len, char *str)
{
	char	*recup;
	int		ret;
	size_t	i;

	i = 0;
	recup = NULL;
	ret = options.flags.width - len;
	if (ret < 0)
		ret = 0;
	if (options.flags.moins)
		str = ft_strjoinandfree(str, ft_putspace_d(ret), 3);
	else
		str = ft_flagspcezero_no_minus_d(options, ret, str);
	return (str);
}

char		*ft_flagspcezero_no_minus_d(t_options options, int ret, char *str)
{
	char	*recup;

	recup = NULL;
	if (options.flags.zero == 1 && options.flags.space == 1)
		recup = ft_strjoinandfree(ft_putspace_d(1),
			ft_putzero_d(ret - 1, str), 3);
	else if (options.flags.zero == 1)
		recup = ft_putzero_d(ret, str);
	else if (!ft_strchr(str, '-') && options.flags.space == 1
		&& options.flags.width == 0 && options.specifier == 'd')
		recup = ft_putspace_d(1);
	else if (options.flags.space == 1 || options.flags.width > 0)
		recup = ft_putspace_d(ret);
	str = ft_strjoinandfree(recup, str, 3);
	return (str);
}
