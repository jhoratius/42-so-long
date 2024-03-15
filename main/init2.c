/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:02:04 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/15 13:33:39 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// void	malloc_hitboxs(t_complete *s)
// {
// 	s->p_hbox = malloc(sizeof(t_hitbox));
// 	if(!s->p_hbox)
// 		return ;
// 	s->c_hbox = malloc(sizeof(t_hitbox));
// 	if(!s->c_hbox)
// 		return ;
// 	s->ex_hbox = malloc(sizeof(t_hitbox));
// 	if(!s->ex_hbox)
// 		return ;
// 	s->e_atk_hbox = malloc(sizeof(t_hitbox));
// 	if(!s->e_atk_hbox)
// 		return ;
// 	s->p_atk_hbox = malloc(sizeof(t_hitbox));
// 	if(!s->p_atk_hbox)
// 		return ;
// }

void	init_hitboxs(t_complete *s)
{
	s->p_hbox.x = s->px + s->p_velocity_x + 11 * SCALE;
	s->p_hbox.y = s->py + s->p_velocity_y + 10 * SCALE;
	s->p_hbox.width = 20 * SCALE - 24;
	s->p_hbox.height = 21 * SCALE;

	s->c_hbox.x = 0;
	s->c_hbox.y = 0;
	s->c_hbox.width = 32;
	s->c_hbox.height = 32;

	s->ex_hbox.x = 0;
	s->ex_hbox.y = 0;
	s->ex_hbox.width = 32;
	s->ex_hbox.height = 32;

	s->e_atk_hbox.x = 0;
	s->e_atk_hbox.y = 0;
	s->e_atk_hbox.width = 32;
	s->e_atk_hbox.height = 32;

	s->p_atk_hbox.x = 0;
	s->p_atk_hbox.y = 0;
	s->p_atk_hbox.width = 32;
	s->p_atk_hbox.height = 32;
}


