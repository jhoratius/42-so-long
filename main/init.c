/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:56:03 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/15 14:11:56 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int		initialisation(t_complete *s)
{
	void	*mlx;
	void	*win;
	t_img	*img;

	s->mlx = NULL;
	s->win = NULL;
	s->img = NULL;
	mlx = mlx_init();
	if (!mlx)
		return (0);
	win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "Sticky Robot");
	if (!win)
		return (0);
	img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!img)
		return (0);
	s->img = img;
	s->mlx = mlx;
	s->win = win;
	return(1);
}

void	affectation_values(t_complete *s)
{
	s->px = 80;
	s->py = 115;
	s->p_flip = false;
	s->en_flip = false;
	s->atk_flip = false;
	s->life_points = 5;
	s->ex = 0;
	s->ey = 0;
	s->enx = 500;
	s->eny = 500;
	s->en_attack = false;
	s->p_velocity_x = 0;
	s->p_velocity_y = 0;
	s->has_jumped = false;
	s->running = false;
	s->p_atk = false;
	s->open_exit = false;
	s->end_game = false;
	s->end_attack = false;
	s->hit = false;
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
	s->collectable = load_xpm_image(s, "./sprites/collectible/cube0.xpm");
	s->exit = load_xpm_image(s, "./sprites/exit/portal0.xpm");
	s->floor = load_xpm_image(s, "./sprites/map/floor_industrial.xpm");
	s->barrier = load_xpm_image(s, "./sprites/map/wall_industrial.xpm");
	s->player = load_xpm_image(s, "./sprites/character/passive/pass0.xpm");
	s->p_run_f[0] = load_xpm_image(s, "./sprites/character/run/run0.xpm");
	s->enemy = load_xpm_image(s, "./sprites/enemies/enemy1/init0.xpm");
	s->atk_enemy_f[0] = load_xpm_image(s, "./sprites/enemies/enemy_atk/attack0.xpm");
	s->exit_banner = load_xpm_image(s, "./sprites/banner/banner3.xpm");
	s->lose_banner = load_xpm_image(s, "./sprites/banner/banner2.xpm");
	s->map = load_map("./maps/map_custom.ber");
	s->e_attack = load_xpm_image(s, "./sprites/enemies/Shot1.xpm");
	s->atk_unit_f[0] = load_xpm_image(s, "./sprites/character/atk/atk_p0.xpm");
}

void	affectation_frames(t_complete *s)
{
	s->p_curr_f = 0;
	s->p_last_f_t = 0;
	s->pr_curr_f = 0;
	s->pr_last_f_t = 0;
	s->c_curr_f = 0;
	s->c_last_f_t = 0;
	s->e_curr_f = 0;
	s->e_last_f_t = 0;
	s->en_curr_f = 0;
	s->en_last_f_t = 0;
	s->en_atk_curr_f = 0;
	s->en_atk_last_f_t = 0;
	s->last_attack_frame = 0;
	s->atk_u_curr_f = 0;
	s->unite_atk_last_f_t = 0;
}

void	all_affectations(t_complete *s)
{
	affectation_values(s);
	affectation_sprites(s);
	affectation_frames(s);
	init_hitboxs(s);
	get_c_pos(s);
	get_enemy_pos(s);
	get_exit_pos(s);
	character_animated(s);
	collectible_animated(s);
	exit_animated(s);
	enemy_animated(s);
}