/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:57:38 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/26 16:34:48 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	enter_exit(t_complete *s)
{
	t_hitbox	*player;
	t_hitbox	*exit;

	player = (t_hitbox *)malloc(sizeof(t_hitbox));
	exit = (t_hitbox *)malloc(sizeof(t_hitbox));
	player->x = s->px + s->p_velocity_x + 11 * SCALE;
	player->y = s->py + s->p_velocity_y + 10 * SCALE;
	player->width = 20 * SCALE - 24;
	player->height = 21 * SCALE;
	exit->x = s->ex + 11 * SCALE;
	exit->y = s->ey + 10 * SCALE;
	exit->width = 20 * SCALE - 24;
	exit->height = 21 * SCALE;
	if (collide(*player, *exit) && s->collectables == 0)
		s->end_game = true;
	free(player);
	free(exit);
}

void	get_e_pos(t_complete *s)
{
	int	i;
	int	j;

	i = -1;
	while (s->map[++i])
	{
		j = 0;
		while (s->map[i][j++])
		{
			if (s->map[i][j] == 'E')
			{
				s->ex = j * 32 * SCALE;
				s->ey = i * 32 * SCALE;
			}
		}
	}
}
