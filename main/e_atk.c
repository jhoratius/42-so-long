/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_atk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:24:25 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/11 17:26:58 by jhoratiu         ###   ########.fr       */
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
		printf("charx : %d\n", charx);
		s->dest_x[0] = charx;
		s->dest_y[0] = chary;
		s->atk_launched = true;
	}
}

void	laser_rotation(t_complete *s)
{
	int		dx;
	int		dy;
	double	angleRad;
	double	angleDeg;

	dx = s->px + s->p_velocity_x + 11 * SCALE;
	dy = s->py + s->p_velocity_y + 10 * SCALE;
	// angleRad = atan2(dy, dx);
	angleDeg = angleRad * (180.0 / M_PI);
}