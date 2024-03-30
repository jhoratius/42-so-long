/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprintf_verifs2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:50:13 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/30 17:43:05 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ftsprintf.h"

int	ft_swrite_unsigned_decimal(unsigned int n, char *buff)
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
		ft_swrite_unsigned_decimal(n / 10, buff);
		i++;
	}
	ft_sputchar(n % 10 + '0', &buff);
	i++;
	return (i);
}

void	ft_swrite_hexadecimal(unsigned int n, char c, char *buff)
{
	if (c == 'x')
		ft_sputnbr_base(n, "0123456789abcdef", buff);
	else if (c == 'X')
		ft_sputnbr_base(n, "0123456789ABCDEF", buff);
}

int	ft_shexa_conditions(int n, int next)
{
	if (n < 48 || n > 57)
		return (0);
	if (n == next)
		return (0);
	return (1);
}

void	ft_sputnbr_base(unsigned long n, char *base, char *buff)
{
	int	i;
	int	buf[100];
	int	base_len;

	i = 0;
	base_len = ft_strlen(base);
	if (n == 0)
	{
		ft_sputchar('0', &buff);
		return ;
	}
	if (n < 0)
	{
		ft_sputchar('-', &buff);
		n = -n;
	}
	while (n)
	{
		buf[i++] = n % base_len;
		n /= base_len;
	}
	while (--i >= 0)
		ft_sputchar(base[buf[i]], &buff);
}
