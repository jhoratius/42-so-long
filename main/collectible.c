/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:14:45 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/02/29 15:22:21 by jhoratiu         ###   ########.fr       */
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

int	collect_a_unit(t_complete *param)
{
	t_hitbox	*player;
	t_hitbox	*collectible;
	int			k;
	int			i;
	int			j;
	
	i = 0;
	player = malloc(sizeof(t_hitbox));
	collectible = malloc(sizeof(t_hitbox));
	player->x = param->px;
	player->y = param->py;
	player->width = 32 * SCALE;
	player->height = 32 * SCALE;
	if(param->collectables == 0)
		param->open_exit = 1;
	while(param->map[i])
	{
		j = 0;
		while(param->map[i][j])
		{
			k = 0;
			while(k < param->collectables)
			{
				collectible->x = param->cx[k];
				collectible->y = param->cy[k];
				collectible->width = 32 * SCALE;
				collectible->height = 32 * SCALE;
				if (collide(*player, *collectible))
				{
					change_map_values(param, k, i, j);
					return (1);
				}
				k++;
			}
			j++;
			k = 0;
		}
		i++;
	}
}

void	change_map_values(t_complete *param, int k, int i, int j)
{
	printf("cx : %d\n", param->cx[k]);
	printf("cy : %d\n", param->cy[k]);
	param->cx[k] = -1;
	param->cy[k] = -1;
	param->collectables--;
	param->collected[k] = 1;
	param->map[i][j] = '0';
	printf("collectables : %d\n", param->collectables);
	printf("collected : %d\n", param->collected[k]);
	printf("k : %d\n", k);
	printf("cx : %d\n", param->cx[k]);
	printf("cy : %d\n", param->cy[k]);
}

// param->cx[i] = -1;
// param->cy[i] = -1;
// param->collectables--;
// param->collected[j] = 1;
// param->map[y][x] = '0';
