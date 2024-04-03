/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:51:59 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/04/03 15:09:12 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_writenbr(char *str, size_t n, char sign, size_t length)
{
	size_t		i;
	long long	nb;

	nb = n;
	i = 0;
	if (sign == '-')
	{
		str[0] = '-';
		nb = -n;
		length++;
		i++;
	}
	while (nb > 0)
	{
		str[length - i - 1] = (nb % 10) + '0';
		nb = nb / 10;
		i++;
	}
}

char	ft_sign(int n)
{
	if (n < 0)
		return ('-');
	return ('+');
}

char	*ft_itoa(int n)
{
	char	*str;
	char	sign;
	size_t	count;
	size_t	num;

	sign = ft_sign(n);
	num = n;
	count = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (sign == '-')
	{
		num = -num;
		count++;
	}
	while (num > 0)
	{
		num /= 10;
		count++;
	}
	str = ft_calloc((count + 1), sizeof(char));
	if (!str)
		return (NULL);
	ft_writenbr(str, n, sign, count);
	return (str);
}

char	*ft_strdup(const char *s)
{
	const char	*str;
	char		*cpy_str;
	int			length;
	int			i;

	str = s;
	length = ft_strlen((char *)str);
	i = 0;
	cpy_str = (char *)malloc(length + 1);
	if (cpy_str != NULL)
	{
		while (str[i])
		{
			cpy_str[i] = str[i];
			i++;
		}
		cpy_str[i] = '\0';
	}
	return (cpy_str);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
