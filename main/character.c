/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:55:31 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/04/03 15:59:23 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	adjust_velocity_x(t_complete *game, float vx)
{
	const float	precision = 0.5;
	const bool	vx_positive = vx > 0;
	bool		collide_x;

	collide_x = check_collision(game, game->w_hbox);
	while (((vx_positive && vx > 0) || (!vx_positive && vx < 0)) && collide_x)
	{
		if (vx_positive)
			vx -= precision;
		else if (!vx_positive)
			vx += precision;
	}
	if ((vx_positive && vx < 0) || (!vx_positive && vx > 0))
		vx = 0;
	game->px += vx;
}

void	adjust_velocity_y(t_complete *game, float vy)
{
	const float	precision = 0.5;
	const bool	vy_positive = vy > 0;
	float		p_vy;
	bool		collide_y;

	p_vy = game->p_velocity_y;
	collide_y = check_collision(game, game->w_hbox);
	while (collide_y && fabsf(game->p_velocity_y) > precision)
	{
		if (vy_positive)
			game->p_velocity_y -= precision;
		else if (!vy_positive)
			game->p_velocity_y += precision;
	}
	vy = game->p_velocity_y;
	game->p_velocity_y = p_vy;
	if (collide_y)
	{
		vy = 0;
		game->p_velocity_y = 0;
	}
	game->py += vy;
}

void	character_moves(t_complete *param)
{
	bool		collision;

	collision = check_collision(param, param->w_hbox);
	param->p_velocity_x = (2 * SCALE) * (param->keys[XK_d] - param->keys[XK_a]);
	if (param->keys[XK_w] && abs(param->p_velocity_y < 0.5) && !param->jumped)
	{
		param->p_velocity_y = -5;
		param->jumped = true;
	}
	else if (param->keys[XK_s])
		param->p_velocity_y = 5;
	if (collision && param->jumped)
		param->jumped = false;
	param->p_velocity_y += (9.81 * 0.016) * (SCALE / 2);
	if (param->keys[XK_d] - param->keys[XK_a])
	{
		param->running = true;
		param->p_flip = (param->keys[XK_d] - param->keys[XK_a]) < 0;
	}
	else
		param->running = false;
	adjust_velocity_x(param, param->p_velocity_x);
	adjust_velocity_y(param, param->p_velocity_y);
}

void	get_p_pos(t_complete *s)
{
	int		x;
	int		y;

	y = 0;
	while (s->map[y])
	{
		x = 0;
		while (s->map[y][x])
		{
			if (s->map[y][x] == 'P')
			{
				s->ppx = x;
				s->ppy = y;
				s->px = x * 32 * SCALE;
				s->py = y * 32 * SCALE;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	update_hb_p(t_complete *s)
{
	s->p_hbox.x = s->px + s->p_velocity_x + 11 * SCALE;
	s->p_hbox.y = s->py + s->p_velocity_y + 10 * SCALE;
	s->p_hbox.width = 20 * SCALE - 24;
	s->p_hbox.height = 21 * SCALE;
}
