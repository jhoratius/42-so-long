/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_verifs2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:50:13 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/02/19 10:52:46 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ftprintf.h"

int	ft_write_unsigned_decimal(unsigned int n, char *buff)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		*buff = '-';
		(*buff)++;
		i++;
		n = -n;
	}
	if (n > 9)
	{
		ft_write_unsigned_decimal(n / 10, buff);
		i++;
	}
	ft_putchar(n % 10 + '0', buff);
	i++;
	return (i);
}

void	ft_write_hexadecimal(unsigned int n, char c, char *buff)
{
	if (c == 'x')
		ft_putnbr_base(n, "0123456789abcdef", buff);
	else if (c == 'X')
		ft_putnbr_base(n, "0123456789ABCDEF", buff);
}

int	ft_hexa_conditions(int n, int next)
{
	if (n < 48 || n > 57)
		return (0);
	if (n == next)
		return (0);
	return (1);
}

void	ft_putnbr_base(unsigned long n, char *base, char *buff)
{
	int	i;
	int	buf[100];
	int	base_len;

	i = 0;
	base_len = ft_strlen(base);
	if (n == 0)
	{
		ft_putchar('0', buff);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-', buff);
		n = -n;
	}
	while (n)
	{
		buf[i++] = n % base_len;
		n /= base_len;
	}
	while (--i >= 0)
		ft_putchar(base[buf[i]], buff);
}
