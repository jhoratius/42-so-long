/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprintf_verifs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:40:18 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/30 17:42:50 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ftsprintf.h"

void	ft_sputchar(char c, char **buff)
{
	**buff = c;
	*buff += 1;
}

int	ft_swrite_string(char *str, char **buff)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		ft_sputchar(str[i], buff);
		*buff += 1;
		i++;
	}
	return (i);
}

void	ft_swrite_pointer(void *ptr, char **buff)
{
	if (ptr == NULL)
		return ;
	**buff = '0';
	*buff += 1;
	**buff = 'x';
	*buff += 1;
	ft_sputnbr_base((unsigned long)ptr, "0123456789abcdef", *buff);
}

int	ft_swrite_decimal(int n, char **buff)
{
	int		i;

	i = 0;
	if (n > 9)
	{
		i += ft_swrite_decimal(n / 10, buff);
	}
	ft_sputchar(n % 10 + '0', buff);
	i++;
	return (i);
}
