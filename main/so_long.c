/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:54:09 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/04/05 13:29:42 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_param(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	if (ft_strlen(str) < 5)
	{
		write(1, "File doesn't have the right extension\n", 38);
		return (0);
	}
	if (str[i] != 'r' || str[i - 1] != 'e'
		|| str[i - 2] != 'b' || str[i - 3] != '.' || !(str[i - 4] != '/'))
	{
		write(1, "Wrong file extension\n", 21);
		write(1, "Exiting the program\n", 20);
		return (0);
	}
	return (1);
}

int	on_update(t_complete *s)
{
	char	*moves;

	moves = ft_itoa(s->nb_pas);
	character_moves(s);
	clear_screen(s->img, 0x00000000);
	draw_map(s, s->map);
	collect_a_unit(s, s->p_hbox, s->c_hbox);
	enter_exit(s);
	ft_draws1(s);
	update_hb_p(s);
	mlx_put_image_to_window(s->mlx, s->win, s->img, 0, 0);
	print_steps(s, moves);
	free(moves);
	return (0);
}

int	main(int ac, char **av)
{
	t_complete	s;

	if (ac < 2 || !check_param(av[1]))
		return (1);
	s = (t_complete){0};
	s.map = load_map(&s, av[1]);
	s.map_copy = load_map(&s, av[1]);
	if (!s.map || !s.map_copy)
		return (1);
	if (!init(&s) || !parse_map(&s))
		return (write(1, "Exit the program\n", 18), 1);
	if (!check_paths(&s))
		return (write(1, "Wrong path\n", 12), 1);
	if (!all_affectations(&s))
		return (write(1, "Exit the program\n", 18), 1);
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
