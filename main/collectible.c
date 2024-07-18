/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:14:45 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/04/08 14:18:57 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	get_c_pos(t_complete *s)
{
	int	i;
	int	j;
	int	k;

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

void	collect_a_unit(t_complete *s, t_hitbox player, t_hitbox item)
{
	int			x;
	int			y;
	int			k;

	if (s->collectables == 0)
		s->open_exit = 1;
	k = 0;
	y = -1;
	while (s->map[++y])
	{
		x = -1;
		while (s->map[y][++x])
		{
			if (s->map[y][x] == 'C')
			{
				item.x = x * 32 * SCALE;
				item.y = y * 32 * SCALE;
				item.width = 32 * SCALE;
				item.height = 32 * SCALE;
				if (collide(player, item))
					change_map_values(s, k);
				k++;
			}
		}
	}
}

void	change_map_values(t_complete *s, int k)
{
	int	i;

	i = 0;
	if (s->collected[k] == 1)
		return ;
	s->collected[k] = 1;
	s->collectables--;
	while (i < s->collectible_count)
		i++;
}

bool	are_collecs_well_allocated(t_complete *s)
{
	s->cx = (int *)malloc(s->c_count * sizeof(int));
	if (!s->cx)
		return (false);
	s->cy = (int *)malloc(s->c_count * sizeof(int));
	if (!s->cy)
	{
		free(s->cx);
		return (false);
	}
	s->collected = (int *)malloc(s->c_count * sizeof(int));
	if (!s->collected)
	{
		free(s->cx);
		free(s->cy);
		return (false);
	}
	ft_bzero(s->cx, s->c_count * sizeof(int));
	ft_bzero(s->cy, s->c_count * sizeof(int));
	ft_bzero(s->collected, s->c_count * sizeof(int));
	return (true);
}
