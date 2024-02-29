/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:57:38 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/02/29 17:50:40 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	enter_exit(t_complete *s)
{
	t_hitbox	*player;
	t_hitbox	*exit;

	player = (t_hitbox *)malloc(sizeof(t_hitbox));
	exit = (t_hitbox *)malloc(sizeof(t_hitbox));
	player->x = s->px;
	player->y = s->py;
	player->width = 32 * SCALE;
	player->height = 32 * SCALE;
	exit->x = s->ex;
	exit->y = s->ey;
	exit->width = 32 * SCALE;
	exit->height = 32 * SCALE;
	if (collide(*player, *exit))
	{
		printf("You win!\n");
		load_xpm_image(s, "sprites/banner/banner0.xpm");
		ft_draw_sprite(s, s->exit_banner, 0, 0, false);
	}
}

void	load_banner(t_complete *s)
{
	if (s->collected[0] == 1 && s->collected[1] == 1 && s->collected[2] == 1)
	{
		s->open_exit = true;
	}
}