/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:54:09 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/20 14:57:28 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int on_update(t_complete *s)
{
	character_moves(s);
	clear_screen(s->img, 0x00000000);
	draw_map(s, s->map);
	collect_a_unit(s);
	enter_exit(s);
	ft_draws1(s);
	mlx_put_image_to_window(s->mlx, s->win, s->img, 0, 0);
	return (0);
}

int main(int ac, char **av)
{
	t_complete	s;

	s = (t_complete){0};
	s.map = load_map(&s, av[1]);
	if(!s.map)
		return (0);
	// parse_map(&s);
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
