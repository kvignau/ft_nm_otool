/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 12:30:59 by kvignau           #+#    #+#             */
/*   Updated: 2015/11/26 16:35:21 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	nb;

	i = 0;
	neg = 0;
	nb = 0;
	while (str[i] == '\n' || str[i] == ' ' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg++;
		i++;
	}
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]))
			nb = (nb * 10) + (str[i] - '0');
		else
			return (neg != 0 ? (nb * -1) : (nb));
		i++;
	}
	return (neg != 0 ? (nb * -1) : (nb));
}
