/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_atk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:35:38 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/13 14:50:58 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	attack_u_collision(t_complete *s)
{
	t_hitbox	*attack;
	t_hitbox	*unite;

	attack = malloc(sizeof(t_hitbox));
	if(!attack)
		return ;
	unite = malloc(sizeof(t_hitbox));
	if(!unite)
		return ;
	attack->x = s->uax[0];
	attack->y = s->uay[0];
	attack->width = 32 * SCALE;
	attack->height = 32 * SCALE;
	unite->x = s->enx;
	unite->y = s->eny;
	unite->width = 32 * SCALE;
	unite->height = 32 * SCALE;
	if(collide(*attack, *unite))
		printf("DAMAGES 2\n");
	free(attack);
	free(unite);
}

void	attack_unite_entity(t_complete *s)
{
	float	speed;
	float	length;
	float	dx;
	float	dy;

	speed = 6;
	if(getms() - s->last_attack_frame > 1000)
	{
		s->uax[0] = s->px + s->p_velocity_x + 11 * SCALE;
		s->uay[0] = s->py + s->p_velocity_y + 10 * SCALE;
        s->ax[0] *= speed;
		s->last_attack_frame = getms();
	}
}