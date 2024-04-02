/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:56:03 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/04/02 13:53:30 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	initialisation(t_complete *s)
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

void	affectation_values(t_complete *s)
{
	s->px = 0;
	s->py = 0;
	s->p_flip = false;
	s->en_flip = false;
	s->ex = 0;
	s->ey = 0;
	s->enx = 500;
	s->eny = 500;
	s->p_velocity_x = 0;
	s->p_velocity_y = 0;
	s->jumped = false;
	s->running = false;
	s->open_exit = false;
	s->end_game = false;
	*s->cx = (int){0};
	*s->cy = (int){0};
	*s->collected = (int){0};
	*s->ax = (int){0};
	*s->ay = (int){0};
	*s->uax = (int){0};
	*s->uay = (int){0};
	*s->dir_x = (float){0};
	*s->dir_y = (float){0};
}

void	affectation_sprites(t_complete *s)
{
	s->player = load_xpm_image(s, "./sprites/character/passive/pass0.xpm");
	s->collectable = load_xpm_image(s, "./sprites/collectible/cube0.xpm");
	s->exit = load_xpm_image(s, "./sprites/exit/portal3.xpm");
	s->floor = load_xpm_image(s, "./sprites/map/floor_industrial.xpm");
	s->barrier = load_xpm_image(s, "./sprites/map/wall_industrial.xpm");
	s->enemy = load_xpm_image(s, "./sprites/enemies/enemy1/init0.xpm");
	s->exit_banner = load_xpm_image(s, "./sprites/banner/banner2.xpm");
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

void	all_affectations(t_complete *s)
{
	affectation_values(s);
	affectation_sprites(s);
	init_hitboxs(s);
	get_e_pos(s);
	get_c_pos(s);
	get_p_pos(s);
	s->map_width = 0;
	s->p_count = 0;
	s->c_count = 0;
	s->e_count = 0;
	s->c_count2 = 0;
	s->e_count2 = 0;
	s->path_jump = 0;
	s->nb_pas = 0;
}
