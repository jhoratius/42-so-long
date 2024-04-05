/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:56:03 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/04/05 14:26:56 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	init(t_complete *s)
{
	void	*mlx;
	void	*win;
	t_img	*img;

	s->mlx = NULL;
	s->win = NULL;
	s->img = NULL;
	mlx = mlx_init();
	if (!mlx)
		return (check_leaks(s), 0);
	win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "Sticky Robot");
	if (!win)
		return (check_leaks(s), 0);
	img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!img)
		return (check_leaks(s), 0);
	s->img = img;
	s->mlx = mlx;
	s->win = win;
	printf("Initialisation is valid\n");
	return (1);
}

bool	are_sprites_well_initiated(t_complete *s)
{
	s->player = load_xpm_image(s, "./sprites/character/robot.xpm");
	if (!s->player)
		return (false);
	s->collectable = load_xpm_image(s, "./sprites/collectible/cube.xpm");
	if (!s->collectable)
		return (false);
	s->exit = load_xpm_image(s, "./sprites/exit/portal.xpm");
	if (!s->exit)
		return (false);
	s->floor = load_xpm_image(s, "./sprites/map/floor_industrial.xpm");
	if (!s->floor)
		return (false);
	s->barrier = load_xpm_image(s, "./sprites/map/wall_industrial.xpm");
	if (!s->barrier)
		return (false);
	return (true);
}

void	init_values(t_complete *s)
{
	s->px = 0;
	s->py = 0;
	s->ex = 0;
	s->ey = 0;
	s->p_velocity_x = 0;
	s->p_velocity_y = 0;
	s->collectible_count = 0;
	s->collectables = 0;
	s->map_width = 0;
	s->map_height = 0;
	s->p_count = 0;
	s->c_count = 0;
	s->e_count = 0;
	s->c_count2 = 0;
	s->e_count2 = 0;
	s->path_jump = 0;
	s->nb_pas = 0;
	s->p_flip = false;
	s->jumped = false;
	s->running = false;
	s->open_exit = false;
	s->end_game = false;
}

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
	s->w_hbox.x = 0;
	s->w_hbox.y = 0;
	s->w_hbox.width = 32;
	s->w_hbox.height = 32;
}

int	all_affectations(t_complete *s)
{
	if(!(are_collecs_well_allocated(s)))
	{
		check_leaks(s);
		return (write(1, "Memory allocation failed\n", 25), 0);
	}
		
	init_values(s);
	if(!(are_sprites_well_initiated(s)))
	{
		check_leaks(s);
		return (write(1, "Sprites failed to load\n", 24), 0);
	}
	init_hitboxs(s);
	get_e_pos(s);
	get_c_pos(s);
	get_p_pos(s);
	return (1);
}
