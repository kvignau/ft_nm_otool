/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 16:49:57 by kvignau           #+#    #+#             */
/*   Updated: 2016/02/25 16:50:00 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_bin(void *arg, t_options *options)
{
	size_t		len;
	char		*str;

	str = NULL;
	len = 0;
	str = ft_cast_ui(arg, options->modifier, 2);
	if (str)
		len = ft_strlen(str);
	if (options->precision >= 0)
		str = ft_precision_d(str, *options, len);
	else
		str = ft_flagspacezero_d(*options, len, str);
	return (str);
}

static char		**ft_create_color(void)
{
	char		**color;

	color = (char **)malloc(sizeof(char *) * 20);
	color[0] = "red";
	color[1] = "blue";
	color[2] = "cyan";
	color[3] = "black";
	color[4] = "green";
	color[5] = "brown";
	color[6] = "default";
	color[7] = "magenta";
	color[8] = "bold red";
	color[9] = "bold blue";
	color[10] = "bold cyan";
	color[11] = "light grey";
	color[12] = "bold black";
	color[13] = "bold green";
	color[14] = "bold brown";
	color[15] = "bold default";
	color[16] = "bold magenta";
	color[17] = "bold light grey";
	color[18] = "eoc";
	color[19] = NULL;
	return (color);
}

static char		**ft_create_code(void)
{
	char		**code;

	code = (char **)malloc(sizeof(char *) * 20);
	code[0] = RED;
	code[1] = BLUE;
	code[2] = CYAN;
	code[3] = BLACK;
	code[4] = GREEN;
	code[5] = BROWN;
	code[6] = DEFAULT;
	code[7] = MAGENTA;
	code[8] = BOLD_RED;
	code[9] = BOLD_BLUE;
	code[10] = BOLD_CYAN;
	code[11] = LIGHT_GREY;
	code[12] = BOLD_BLACK;
	code[13] = BOLD_GREEN;
	code[14] = BOLD_BROWN;
	code[15] = BOLD_DEFAULT;
	code[16] = BOLD_MAGENTA;
	code[17] = BOLD_LIGHT_GREY;
	code[18] = END;
	code[19] = NULL;
	return (code);
}

static void		ft_searchcolor(char **color, char *str, int *i, int j)
{
	char	**code;
	int		x;

	x = 0;
	while (color[x])
	{
		if (ft_strcmp(str, color[x]) == 0)
		{
			code = ft_create_code();
			write(1, code[x], ft_strlen(code[x]));
			free(color);
			free(code);
			*i = ((*i) + j) + 2;
			return ;
		}
		x++;
	}
}

void			ft_color(const char *restrict format, int *i)
{
	int			j;
	char		*str;
	char		**color;

	j = 0;
	color = ft_create_color();
	while (format[*i + j] && format[*i + j] != '}')
		j++;
	str = ft_strnew(j);
	j = 0;
	while (format[*i + j] && format[*i + j] != '}')
	{
		str[j] = format[*i + j];
		j++;
	}
	if (format[(*i) + j] != '}')
	{
		free(color);
		free(str);
		return ;
	}
	ft_searchcolor(color, str, i, j);
	free(str);
	(*i)--;
}
