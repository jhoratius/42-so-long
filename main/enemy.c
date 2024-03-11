/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:29:12 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/11 17:13:28 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	get_enemy_pos(t_complete *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;

	while (s->map[i])
	{
		j = 0;
		while (s->map[i][j])
		{
			if(s->map[i][j] == 'A')
			{
				s->enx = j * 32 * SCALE;
				s->eny = i * 32 * SCALE;
				printf("enemy pos : %d, %d\n", s->enx, s->eny);
			}
			j++;
		}
		i++;
	}
	return ;
}

void	follow_entity(t_complete *s)
{
	int	charx;
	int	chary;
	int	enmx;
	int	enmy;

	enmx = s->enx + 31;
	enmy = s->eny;
	charx = s->px + s->p_velocity_x + 11 * SCALE;
	chary = s->py + s->p_velocity_y + 10 * SCALE;
	if(charx < enmx)
		s->en_flipped = true;
	else if(charx > enmx)
		s->en_flipped = false;
}

void	find_entity(t_complete *s)
{
	int	p_px;
	int	p_py;
	int	p_ex;
	int p_ey;
	int rad;

	p_px = s->px + s->p_velocity_x + + 11 * SCALE;
	p_py = s->py + s->p_velocity_y + 10 * SCALE;
	p_ex = s->enx + 31;
	p_ey = s->eny;
	rad = 150 * SCALE;
	if((p_px - p_ex) * (p_px - p_ex) + (p_py - p_ey) * (p_py - p_ey) <= rad * rad)
	{
		s->en_attack = true;
		printf("ATTACK\n");
	}
	else
		s->en_attack = false;
}

void	attack_entity(t_complete *s)
{
	int		i;
	int		speed;

	i = 0;
	speed = 5;
	if(getms() - s->last_attack_frame > 600)
	{
		s->ax[0] = s->enx - 35;
		s->ay[0] = s->eny + 10;
		s->last_attack_frame = getms();
	}
	printf("flipped: %d\n", s->atk_flipped);
	printf("launched: %d\n", s->atk_launched);

	if(s->atk_flipped && s->atk_launched)
	{
		printf("ax : %d\n", s->ax[0]);
		s->ax[0] -= speed;
	}
	else if(!(s->atk_flipped) && s->atk_launched)
	{
		printf("TEST 2");
		s->ax[0] += speed;
	}
}