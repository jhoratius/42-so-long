/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:54:09 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/13 18:23:49 by jhoratiu         ###   ########.fr       */
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

	// Enemy
	collect_a_unit(param);
	enter_exit(param);
	follow_entity(param);
	follow_entity_a(param, param->enx - 55, param->eny - 30);
	find_entity(param);
	attack_entity(param);
	atk_unite(param);
	attack_collision(param);
	attack_u_collision(param);

	// Draw exit
	ft_draw_sprite(param, param->exit_frames[param->e_current_frame], param->ex, param->ey, false);

	// Draw collectibles
	while(i < param->collectible_count)
	{
		if(!param->collected[i])
			ft_draw_sprite(param, param->collect_frames[param->c_current_frame], param->cx[i], param->cy[i], false);
		i++;
	}
	i = 0;

	// Draw enemies
	if(param->en_attack)
		ft_draw_sprite(param, param->atk_enemy_frames[param->en_atk_current_frame], param->enx, param->eny, param->en_flipped);
	else
		ft_draw_sprite(param, param->enemy_frames[param->en_current_frame], param->enx, param->eny, param->en_flipped);

	// Draw character
	if(param->p_atk)
		ft_draw_sprite(param, param->atk_unit_frames[param->unite_atk_current_frame], param->px, param->py, param->p_flipped);
	else
	{
		if(param->running)
			ft_draw_sprite(param, param->p_run_frames[param->pr_current_frame], param->px, param->py, param->p_flipped);
		else if(!(param->running))
			ft_draw_sprite(param, param->player_frames[param->p_current_frame], param->px, param->py, param->p_flipped);
	}

	if(param->end_game)
		ft_draw_sprite(param, param->exit_banner, param->widthmap * 5 * SCALE, param->heightmap * 2 * SCALE, false);
	if(param->lose_game)
	{
		if(!param->keys[XK_Escape])
			ft_draw_sprite(param, param->lose_banner, param->widthmap * 5 * SCALE, param->heightmap * 2 * SCALE, false);
		else
			mlx_loop_end(param->mlx);
	}
	if(param->atk_launched && !param->end_attack)
		ft_draw_sprite(param, param->e_attack, param->ax[0], param->ay[0], param->atk_flipped);

	// Put all img to window
	mlx_put_image_to_window(param->mlx, param->win, param->img, 0, 0);

	// Animation
		// Character
	if(param->p_atk)
	{
		if (getms() - param->unite_atk_last_frame_time > 100)
		{
			param->unite_atk_last_frame_time = getms();
			param->unite_atk_current_frame++;
			if (param->unite_atk_current_frame >= 4)
			{
				param->unite_atk_current_frame = 0;
				param->p_atk = false;
			}
		}
	}
	else
	{
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
	}

		// Collectibles
	if (getms() - param->c_last_frame_time > 400)
	{
		param->c_last_frame_time = getms();
		param->c_current_frame++;
		if (param->c_current_frame >= 3)
			param->c_current_frame = 0;
	}
		// Exit
	if (getms() - param->e_last_frame_time > 150)
	{
		param->e_last_frame_time = getms();
		param->e_current_frame++;
		if(param->open_exit)
		{
			if (param->e_current_frame >= 4)
				param->e_current_frame = 3;
		}
		else
		{
			if (param->e_current_frame >= 3)
				param->e_current_frame = 0;
		}
	}
		// Enemy
	if(param->en_attack)
	{
		if (getms() - param->en_atk_last_frame_time > 200)
		{
			param->en_atk_last_frame_time = getms();
			param->en_atk_current_frame++;
			if (param->en_atk_current_frame >= 3)
			{
				param->en_atk_current_frame = 0;
				param->end_attack = false;
			}
		}
	}
	else
	{
		if (getms() - param->en_last_frame_time > 400)
		{
			param->en_last_frame_time = getms();
			param->en_current_frame++;
			if (param->en_current_frame >= 4)
				param->en_current_frame = 0;
		}
	}
	
	return (0);
}

int main(void)
{
	t_complete	s;
	int i;

	i = 0;
	s = (t_complete){0};
	if(!(initialisation(&s))){
		free_init(&s);
		mlx_destroy_image(s.mlx, s.img);
		mlx_clear_window(s.mlx, s.win);
		mlx_destroy_window(s.mlx, s.win);
		return(write(1, "fail", 4), 0);
	}
	affectation_values(&s);
	affectation_sprites(&s);
	affectation_frames(&s);
	// affectation_collect(&s);

	// get positions
	get_c_pos(&s);
	get_enemy_pos(&s);
	get_exit_pos(&s);
	// put img to window
	mlx_put_image_to_window(s.mlx, s.win, s.img, 0, 0);
	// animation functions
	character_animated(&s);
	collectible_animated(&s);
	exit_animated(&s);
	enemy_animated(&s);

	// boucle de jeu
	mlx_do_key_autorepeatoff(s.mlx);
	mlx_loop_hook(s.mlx, on_update, &s);
	mlx_hook(s.win, KeyPress, KeyPressMask, key_pressed_hook, &s);
	mlx_hook(s.win, KeyRelease, KeyReleaseMask, key_released_hook, &s);
	mlx_hook(s.win, DestroyNotify, 0, close_hook, &s);
	mlx_loop(s.mlx);
	mlx_do_key_autorepeaton(s.mlx);

	// display_megaman();
	// return (MALLOC_ERROR);
	return (0);
}
