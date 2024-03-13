/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_atk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:24:25 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/13 18:06:21 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	follow_entity_a(t_complete *s, int px, int py)
{
	int	charx;
	int	chary;
	int	point_x;
	int	point_y;

	charx = s->px + s->p_velocity_x + 11 * SCALE;
	chary = s->py + s->p_velocity_y + 10 * SCALE;
	if(!s->atk_launched)
	{
		if(charx < px)
			s->atk_flipped = true;
		else if(charx > px)
			s->atk_flipped = false;
		s->dest_x[0] = charx;
		s->dest_y[0] = chary;
		s->atk_launched = true;
	}
}

void	attack_collision(t_complete *s)
{
	t_hitbox	*attack;
	t_hitbox	*unite;

	attack = malloc(sizeof(t_hitbox));
	if(!attack)
		return ;
	unite = malloc(sizeof(t_hitbox));
	if(!unite)
		return ;
	attack->x = s->ax[0] + 38;
	attack->y = s->ay[0];
	attack->width = 20 * SCALE - 30;
	attack->height = 20 * SCALE;
	unite->x = s->px + s->p_velocity_x + 11 * SCALE;
	unite->y = s->py + s->p_velocity_y + 10 * SCALE;
	unite->width = 20 * SCALE - 24;
	unite->height = 21 * SCALE;
	if(collide(*attack, *unite))
	{
		s->hit = true;
		s->end_attack = true;
		s->lose_game = true;
	}
	free(attack);
	free(unite);
}

void	attack_entity(t_complete *s)
{
	float	speed;
	float	length;
	float	dx;
	float	dy;

	speed = 6;
	if(getms() - s->last_attack_frame > 1000)
	{
		if(s->end_attack)
			return ;
		else
		{
			s->ax[0] = s->enx - 15;
			s->ay[0] = s->eny + 15;
			s->last_attack_frame = getms();
			s->atk_launched = false;
			dx = s->dest_x[0] - s->ax[0];
			dy = s->dest_y[0] - s->ay[0];
			length = sqrt(dx * dx + dy * dy);
			dx /= length;
			dy /= length;
			s->dir_x[0] = dx;
			s->dir_y[0] = dy;
		}
	}
	if(s->atk_launched)
	{
		if(!s->end_attack)
		{
			s->ax[0] += s->dir_x[0] * speed;
			s->ay[0] += s->dir_y[0] * speed;
		}
	}
}

// void	laser_rotation(t_complete *s)
// {
// 	int		dx;
// 	int		dy;
// 	double	angleRad;
// 	double	angleDeg;

// 	dx = s->px + s->p_velocity_x + 11 * SCALE;
// 	dy = s->py + s->p_velocity_y + 10 * SCALE;
// 	// angleRad = atan2(dy, dx);
// 	angleDeg = angleRad * (180.0 / M_PI);
// }