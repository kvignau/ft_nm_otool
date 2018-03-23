/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 11:33:31 by kvignau           #+#    #+#             */
/*   Updated: 2015/12/02 12:22:12 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrev(char *str)
{
	size_t	i;
	size_t	len;
	char	save;

	i = 0;
	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	while (i < len)
	{
		save = str[i];
		str[i] = str[len - 1];
		str[len - 1] = save;
		i++;
		len--;
	}
	return (str);
}
