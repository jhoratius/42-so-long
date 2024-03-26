/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_verifs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:40:18 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/22 14:02:50 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ftprintf.h"

void	ft_putchar(char c, char **buff)
{
	**buff = c;
	*buff += 1;
}

int	ft_write_string(char *str, char **buff)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		ft_putchar(str[i], buff);
		*buff += 1;
		i++;
	}
	return (i);
}

void	ft_write_pointer(void *ptr, char **buff)
{
	if (ptr == NULL)
		return ;
	**buff = '0';
	*buff += 1;
	**buff = 'x';
	*buff += 1;
	ft_putnbr_base((unsigned long)ptr, "0123456789abcdef", *buff);
}

int	ft_write_decimal(int n, char **buff)
{
	int		i;

	i = 0;
	// if (n == -2147483648)
	// {
	// 	ft_putchar('-', **buff);
	// 	i++;
	// 	n = 147483648;
	// }
	// if (n < 0)
	// {
	// 	ft_putchar('-', **buff);
	// 	i++;
	// 	n = -n;
	// }
	if (n > 9)
	{
		i += ft_write_decimal(n / 10, buff);
	}
	ft_putchar(n % 10 + '0', buff);
	i++;
	return (i);
}
