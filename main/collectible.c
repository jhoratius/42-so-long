/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:14:45 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/01 15:14:36 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	get_c_pos(t_complete *param)
{
	int i;
	int j;
	int k;

	i = -1;
	k = 0;
	while (param->map[++i])
	{
		j = 0;
		while (param->map[i][j++])
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
		}
	}
}

int	collect_a_unit(t_complete *s)
{
	t_hitbox	*player;
	int			k;
	int			i;
	int			j;

	i = 0;
	
	player = (t_hitbox *)malloc(sizeof(t_hitbox));
	if(!player)
		return (1);
	s->collectibles = malloc(s->collectables * sizeof(t_hitbox*));
	while(i < s->collectables)
	{
		s->collectibles[i] = (t_hitbox *)malloc(sizeof(t_hitbox));
		i++;
	}
	i = 0;

	if(s->collectables == 0)
		s->open_exit = 1;
	while(s->map[i])
	{
		j = 0;
		while(s->map[i][j])
		{
			k = -1;
			while(++k < s->collectables)
			{
				s->collectibles[k]->x = j;
				s->collectibles[k]->y = i;
				s->collectibles[k]->width = 32 * SCALE;
				s->collectibles[k]->height = 32 * SCALE;
				if (collide(*player, *s->collectibles[k]))
				{
					change_map_values(s, k, i, j);
					return (1);
				}
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