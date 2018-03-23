/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 15:18:27 by kvignau           #+#    #+#             */
/*   Updated: 2015/12/01 17:18:54 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*str;

	str = ft_strnew(len);
	if (str == NULL || s == NULL)
		return (NULL);
	ft_strncpy(str, s + start, len);
	str[len] = '\0';
	return (str);
}
