/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:56:03 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/02/22 14:46:28 by jhoratiu         ###   ########.fr       */
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
	if(!mlx)
		return (1);
	win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "Sticky Robot");
	if (!win)
		return (1);
	img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	if(!img)
		return (1);
	s->img = img;
	s->mlx = mlx;
	s->win = win;
	return(0);
}

void	affectation(t_complete *s)
{
	// affectation des valeurs
	s->px = 128;
	s->py = 128;
	s->cx[0] = 0;
	s->cy[0] = 0;
	s->p_velocity_x = 0;
	s->p_velocity_y = 0;
	s->has_jumped = false;
	s->running = false;

	// mettre les images sur la fenetre
	s->collectable = load_xpm_image(s, "./sprites/collectible/cube0.xpm");
	s->floor = load_xpm_image(s, "./sprites/map/floor_industrial.xpm");
	s->barrier = load_xpm_image(s, "./sprites/map/wall_industrial.xpm");
	s->player = load_xpm_image(s, "./sprites/character/passive/pass0.xpm");
	s->p_run_frames[0] = load_xpm_image(s, "./sprites/character/run/run0.xpm");

	// gestion des frames
	s->p_current_frame = 0;
	s->p_last_frame_time = 0;
	s->pr_current_frame = 0;
	s->pr_last_frame_time = 0;
	s->c_current_frame = 0;
	s->c_last_frame_time = 0;
	s->map = load_map("./maps/map_custom.ber");
	return ;
}
