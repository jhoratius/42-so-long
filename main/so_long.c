/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:54:09 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/02/23 18:11:33 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	time_frames(suseconds_t *last_frame_time, int *current_frame, int time, int number_of_frames)
{
	if (getms() - *last_frame_time > time)
	{
		*last_frame_time = getms();
		*current_frame++;
		if (current_frame >= number_of_frames)
			*current_frame = 0;
	}
}

// check_walls_map()
// {
	
// }

// Boucle hook
int on_update(t_complete *param, t_frames *char_frames)
{
	int i;

	i = 0;
	param->p_velocity_x = 0;
	character_moves(param);
	clear_screen(param->img, 0x00000000);
	draw_map(param, param->map);
	if(param->running)
		ft_draw_sprite(param, param->p_run_frames[param->pr_current_frame], param->px, param->py, param->p_flipped);
	else if(param->running == false)
		ft_draw_sprite(param, param->player_frames[param->p_current_frame], param->px, param->py, param->p_flipped);
	ft_draw_sprite(param, param->collect_frames[param->c_current_frame], param->cx[i], param->cy[i], false);
	// ft_draw_sprite(param, param->collect_frames[param->c_current_frame], param->cx[param->collectables], param->cy[param->collectables], false);
	mlx_put_image_to_window(param->mlx, param->win, param->img, 0, 0);
	if(param->running)
	{
		if (getms() - param->pr_last_frame_time > 200)
		{
			param->pr_last_frame_time = getms();
			param->pr_current_frame++;
			if (param->pr_current_frame >= 5)
				param->pr_current_frame = 0;
		}
		// time_frames(&param->pr_last_frame_time, &param->pr_current_frame, 200, 5);
	}
	else
	{
		if (getms() - param->p_last_frame_time > 200)
		{
			param->p_last_frame_time = getms();
			param->p_current_frame++;
			if (param->p_current_frame >= 4)
				param->p_current_frame = 0;
		}
		// time_frames(&param->p_last_frame_time, &param->p_current_frame, 200, 4);
	}

	if (getms() - param->c_last_frame_time > 400)
	{
		param->c_last_frame_time = getms();
		param->c_current_frame++;
		if (param->c_current_frame >= 4)
			param->c_current_frame = 0;
	}
	// time_frames(&param->c_last_frame_time, &param->c_current_frame, 400, 4);
	return (0);
}

int main(void)
{
	t_complete	s;
	// t_frames	char_frames;
	// t_frames	collect_frames;

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
