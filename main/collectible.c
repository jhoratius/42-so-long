/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:14:45 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/08 12:50:13 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	get_c_pos(t_complete *s)
{
	int i;
	int j;
	int k;

	i = -1;
	k = 0;
	while (s->map[++i])
	{
		j = 0;
		while (s->map[i][j++])
		{
			
			if (s->map[i][j] == 'C')
			{
				s->cx[k] = j * 32 * SCALE;
				s->cy[k] = i * 32 * SCALE;
				s->collectible_count++;
				k++;
			}
		}
	}
	s->collectables = s->collectible_count;
}

int	collect_a_unit(t_complete *s)
{
	t_hitbox	*player;
	t_hitbox	*item;
	int			x;
	int			y;
	int			k;

	player = (t_hitbox *)malloc(sizeof(t_hitbox));
	if(!player)
		return (1);
	item = (t_hitbox *)malloc(sizeof(t_hitbox));
	if(!item)
		return (1);
	player->x = s->px + s->p_velocity_x + 11 * SCALE;
	player->y = s->py + s->p_velocity_y + 10 * SCALE;
	player->width = 20 * SCALE - 24;
	player->height = 21 * SCALE;

	if(s->collectables == 0)
		s->open_exit = 1;
	y = -1;
	k = 0;
	while (s->map[++y])
	{
		x = 0;
		while (s->map[y][x++])
		{
			if (s->map[y][x] == 'C')
			{
				item->x = x * 32 * SCALE;
				item->y = y * 32 * SCALE;
				item->width = 32 * SCALE;
				item->height = 32 * SCALE;
				if (collide(*player, *item))
				{
					change_map_values(s, x, y, k);
					// return (0);
				}
				k++;
			}
		}
	}
	return (0);
}

void	change_map_values(t_complete *s, int x, int y, int k)
{
	int i;

	i = 0;
	if (s->collected[k])
		return ;
	s->collected[k] = 1;
	s->collectables--;
	while(i < s->collectible_count)
		i++;
}
