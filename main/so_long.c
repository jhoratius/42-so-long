/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:54:09 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/15 15:19:22 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int on_update(t_complete *s, t_frames *char_frames)
{
	character_moves(s);
	clear_screen(s->img, 0x00000000);
	draw_map(s, s->map);
	collect_a_unit(s);
	enter_exit(s);
	follow_entity(s);
	follow_entity_a(s, s->enx - 55, s->eny - 30);
	find_entity(s);
	attack_entity(s);
	atk_unite(s);
	attack_collision(s);
	attack_u_collision(s);
	ft_draws1(s);
	ft_draws2(s);
	mlx_put_image_to_window(s->mlx, s->win, s->img, 0, 0);
	all_frames(s);
	return (0);
}

int main(void)
{
	t_complete	s;

	s = (t_complete){0};
	if(!(initialisation(&s))){
		check_leaks(&s);
		return(write(1, "fail", 4), 0);
	}
	else {
		all_affectations(&s);
		mlx_put_image_to_window(s.mlx, s.win, s.img, 0, 0);
		mlx_do_key_autorepeatoff(s.mlx);
		mlx_loop_hook(s.mlx, on_update, &s);
		mlx_hook(s.win, KeyPress, KeyPressMask, key_pressed_hook, &s);
		mlx_hook(s.win, KeyRelease, KeyReleaseMask, key_released_hook, &s);
		mlx_hook(s.win, DestroyNotify, 0, close_hook, &s);
		mlx_loop(s.mlx);
		mlx_do_key_autorepeaton(s.mlx);
		check_leaks(&s);
	}
	return (0);
}
