/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:55:31 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/15 14:11:00 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/so_long.h"

void	adjust_velocity_x(t_complete *game, float vx)
{
	const float	precision = 0.5;
	const bool	vx_positive = vx > 0;
	bool		collide_x;

	collide_x = check_collision(game);
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

void		adjust_velocity_y(t_complete *game, float vy)
{
	const float	precision = 0.5;
	const bool	vy_positive = vy > 0;
	float 		p_vy = game->p_velocity_y;
	bool		collide_y;

	collide_y = check_collision(game);
	while (collide_y && abs(game->p_velocity_y) > precision)
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

void		character_moves(t_complete *param)
{
	bool		collision;

	collision = check_collision(param);
	param->p_velocity_x = (2 * SCALE) * (param->keys[XK_d] - param->keys[XK_a]);
	if (param->keys[XK_w] && fabs(param->p_velocity_y < 0.5) && !param->has_jumped)
	{
		param->p_velocity_y = -5;
		param->has_jumped = true;
	}
	if(collision && param->has_jumped)
		param->has_jumped = false;
	param->p_velocity_y += 9.81 * 0.016;
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
