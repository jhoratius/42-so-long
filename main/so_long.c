/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:54:09 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/02/28 19:33:59 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// void	time_frames(suseconds_t *last_frame_time, int *current_frame, int number_of_frames)
// {
// 	*last_frame_time = getms();
// 	*current_frame++;
// 	if (current_frame >= number_of_frames)
// 		*current_frame = 0;
// }

// check_walls_map()
// {
	
// }

// Boucle hook
int on_update(t_complete *param, t_frames *char_frames)
{
	int i;
	
	i = 0;
	// handle character movement
	character_moves(param);
	clear_screen(param->img, 0x00000000);

	// Draw map
	draw_map(param, param->map);

	// Draw character
	if(param->running)
		ft_draw_sprite(param, param->p_run_frames[param->pr_current_frame], param->px, param->py, param->p_flipped);
	else if(param->running == false)
		ft_draw_sprite(param, param->player_frames[param->p_current_frame], param->px, param->py, param->p_flipped);

	// Draw enemies
	ft_draw_sprite(param, param->enemy_frames[param->en_current_frame], param->enx, param->eny, false);

	// Draw collectibles
	while(i < param->collectables)
	{
		ft_draw_sprite(param, param->collect_frames[param->c_current_frame], param->cx[i], param->cy[i], false);
		i++;
	}
	i = 0;

	// Draw exit
	ft_draw_sprite(param, param->exit_frames[param->e_current_frame], param->ex, param->ey, false);

	// Put all img to window
	mlx_put_image_to_window(param->mlx, param->win, param->img, 0, 0);
	if(param->running)
	{
		if (getms() - param->pr_last_frame_time > 150)
		{
			param->pr_last_frame_time = getms();
			param->pr_current_frame++;
			if (param->pr_current_frame >= 5)
				param->pr_current_frame = 0;
		}
	}
	else
	{
		if (getms() - param->p_last_frame_time > 170)
		{
			param->p_last_frame_time = getms();
			param->p_current_frame++;
			if (param->p_current_frame >= 4)
				param->p_current_frame = 0;
		}
	}
	if (getms() - param->c_last_frame_time > 400)
	{
		param->c_last_frame_time = getms();
		param->c_current_frame++;
		if (param->c_current_frame >= 3)
			param->c_current_frame = 0;
	}

	if (getms() - param->e_last_frame_time > 150)
	{
		param->e_last_frame_time = getms();
		param->e_current_frame++;
		if(param->open_exit)
		{
			if (param->e_current_frame >= 4)
				param->e_current_frame = 0;
		}
		else
		{
			if (param->e_current_frame >= 4)
				param->e_current_frame = 0;
		}
	}

	if (getms() - param->en_last_frame_time > 400)
	{
		param->en_last_frame_time = getms();
		param->en_current_frame++;
		if (param->en_current_frame >= 4)
			param->en_current_frame = 0;
	}
	return (0);
}

int main(void)
{
	t_complete	s;
	int i;
	// t_frames	char_frames;
	// t_frames	collect_frames;
	i = 0;
	s = (t_complete){0};
	if(initialisation(&s)){
		free_init(&s);
		mlx_clear_window(s.mlx, s.win);
		mlx_destroy_window(s.mlx, s.win);
		return(write(1, "fail", 4), 0);
	}
	affectation(&s);
	mlx_put_image_to_window(s.mlx, s.win, s.img, 0, 0);
	character_animated(&s);
	collectible_animated(&s);
	exit_animated(&s);
	enemy_animated(&s);
	get_c_pos(&s);
	get_enemy_pos(&s);

	// boucle de jeu
	mlx_do_key_autorepeatoff(s.mlx);
	mlx_loop_hook(s.mlx, on_update, &s);
	mlx_hook(s.win, KeyPress, KeyPressMask, key_pressed_hook, &s);
	mlx_hook(s.win, KeyRelease, KeyReleaseMask, key_released_hook, &s);
	mlx_hook(s.win, DestroyNotify, 0, close_hook, &s);
	mlx_loop(s.mlx);
	mlx_do_key_autorepeaton(s.mlx);

	// return (MALLOC_ERROR);
	return (0);
}
