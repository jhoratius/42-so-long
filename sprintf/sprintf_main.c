/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprintf_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:41:43 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/30 17:42:27 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ftsprintf.h"

char	*ft_sverifications(char c, va_list *args, char **buff, int *j)
{
	if (c == 'c')
	{
		ft_sputchar(va_arg(*args, int), buff);
		j++;
	}
	else if (c == 's')
		j += ft_swrite_string(va_arg(*args, char *), buff);
	else if (c == 'd' || c == 'i')
		j += ft_swrite_decimal(va_arg(*args, int), buff);
	else if (c == 'u')
		j += ft_swrite_unsigned_decimal(va_arg(*args, unsigned int), *buff);
	else if (c == 'p')
		ft_swrite_pointer(va_arg(*args, void *), buff);
	else if (c == 'x')
		ft_swrite_hexadecimal(va_arg(*args, unsigned int), 'x', *buff);
	else if (c == 'X')
		ft_swrite_hexadecimal(va_arg(*args, unsigned int), 'X', *buff);
	else if (c == '%')
	{
		ft_sputchar('%', buff);
		j++;
	}
	return (*buff);
}

char	*ft_sprintf(char *buff, const char *str, ...)
{
	int		i;
	int		j;
	va_list	args;

	i = 0;
	j = 0;
	if (str == NULL || buff == NULL)
		return (NULL);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			ft_sverifications(str[i + 1], &args, &buff, &j);
			i++;
		}
		else
			ft_sputchar(str[i], &buff);
		i++;
	}
	*buff = '\0';
	return (buff);
}
