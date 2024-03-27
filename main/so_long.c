/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:54:09 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/27 18:47:15 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	on_update(t_complete *s)
{
	// int	moves;

	// moves = ft_itoa(s->nb_pas);
	character_moves(s);
	clear_screen(s->img, 0x00000000);
	draw_map(s, s->map);
	collect_a_unit(s, s->p_hbox, s->c_hbox);
	enter_exit(s);
	ft_draws1(s);
	update_hb_p(s);
	mlx_put_image_to_window(s->mlx, s->win, s->img, 0, 0);
	// mlx_string_put(s->mlx, s->win, 10 * SCALE, 20 * SCALE, 0xFFFFFF, "Nb de pas : ");
	// mlx_string_put(s->mlx, s->win, 10 * SCALE, 40 * SCALE, 0xFFFFFF, ft_itoa(s->nb_pas));
	// free(moves);
	return (0);
}

int	main(int ac, char **av)
{
	t_complete	s;
	int i = -1;

	if (ac <= 1)
		return (0);
	s = (t_complete){0};
	s.map = load_map(&s, av[1]);
	s.map_copy = load_map(&s, av[1]);
	if (!s.map)
		return (0);
	if (!initialisation(&s) || !parse_map(&s))
		return (write(1, "fail\n", 5), 1);
	if(!check_paths(&s))
		return (write(1, "ok\n", 3), 1);
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
	return (0);
}
