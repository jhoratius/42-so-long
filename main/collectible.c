/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:14:45 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/02/28 17:37:50 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	get_c_pos(t_complete *param)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	while (param->map[i])
	{
		j = 0;
		while (param->map[i][j])
		{
			if (param->map[i][j] == 'C')
			{
				if(collect_a_unit(param, j * 32 * SCALE, i * 32 * SCALE) == 1)
				{
					printf("collected : %d\n", param->collected[k]);
					param->map[i][j] = '0';
					continue;
				}
				param->cx[k] = j * 32 * SCALE;
				param->cy[k] = i * 32 * SCALE;
				param->collectables++;
				k++;
			}
			if(param->map[i][j] == 'E')
			{
				param->ex = j * 32 * SCALE;
				param->ey = i * 32 * SCALE;
			}
			j++;
		}
		i++;
	}
}

int	collect_a_unit(t_complete *param, int x, int y)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < param->collectables)
	{
		if (param->cx[i] == x && param->cy[i] == y)
		{
			param->cx[i] = -1;
			param->cy[i] = -1;
			param->collectables--;
			param->collected[j] = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
