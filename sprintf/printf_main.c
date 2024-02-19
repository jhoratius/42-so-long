/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:41:43 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/02/19 14:14:01 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ftprintf.h"

char	*ft_verifications(char c, va_list *args, char **buff, int *j)
{
	if (c == 'c')
	{
		ft_putchar(va_arg(*args, int), buff);
		j++;
	}
	else if (c == 's')
		j += ft_write_string(va_arg(*args, char *), buff);
	else if (c == 'd' || c == 'i')
		j += ft_write_decimal(va_arg(*args, int), buff);
	else if (c == 'u')
		j += ft_write_unsigned_decimal(va_arg(*args, unsigned int), buff);
	else if (c == 'p')
		ft_write_pointer(va_arg(*args, void *), buff);
	else if (c == 'x')
		ft_write_hexadecimal(va_arg(*args, unsigned int), 'x', buff);
	else if (c == 'X')
		ft_write_hexadecimal(va_arg(*args, unsigned int), 'X', buff);
	else if (c == '%')
	{
		ft_putchar('%', buff);
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
			ft_verifications(str[i + 1], &args, &buff, &j);
			i++;
		}
		else
			ft_putchar(str[i], &buff);
		i++;
	}
	*buff = '\0';
	return (buff);
}
