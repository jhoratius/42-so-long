/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:54:09 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/02/19 14:10:25 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

unsigned int get_pixel(t_img *img, int x, int y, bool flipped)
{
	if (flipped)
		return (((int *)img->data)[(int)(y / SCALE) * img->width + img->width - (int)(x / SCALE) - 1]);
	return (((int *)img->data)[(int)(y / SCALE) * img->width + (int)(x / SCALE)]);
}
void	clear_screen(t_img *img, unsigned int color)
{
	int i;
	int j;

	i = 0;
	while (i < img->width)
	{
		j = 0;
		while (j < img->height)
		{
			((int *)img->data)[j * img->width + i] = color;
			j++;
		}
		i++;
	}
}
void	ft_draw_sprite(t_complete *game, t_img *img, int x, int y, bool flipped)
{
	int				i;
	int				j;
	unsigned int	color;

	i = 0;
	while (i < img->width * SCALE)
	{
		j = 0;
		while (j < img->height * SCALE)
		{
			if (j + y < 0 || j + y >= game->img->height || i + x < 0 || i + x >= game->img->width)
			{
				j++;
				continue;
			}
			color = get_pixel(img, i, j, flipped);
			if (color == 0xFF000000)
			{
				j++;
				continue;
			}
			((int *)game->img->data)[(y + j) * game->img->width + (x + i)] = color;
			j++;
		}
		i++;
	}
}

void	*load_xpm_image(t_complete *param, char *imagePath)
{
	void	*ptr;

	printf("Loading %s\n", imagePath);
	ptr = mlx_xpm_file_to_image(param->mlx, imagePath, &param->widthmap, &param->heightmap);
	if(!ptr){
		printf("Error: Unable to load %s\n", imagePath);
		return (NULL);
	}
	return (ptr);
}

void	launch_game(char *map_file)
{
	char **map = load_map(map_file);
	if(!map)
		return ;
	// printf("map : %p\n", map);
}

void		adjust_velocity_x(t_complete *param)
{
	bool		collision;
	const bool		velocity_x = param->p_velocity_x > 0;
	const float		precision = 0.5;

	while(check_collision(param, &(t_hitbox){param->px + param->p_velocity_x, param->py, 32, 32})
		&& ((velocity_x > 0 && param->p_velocity_x > 0) || (velocity_x < 0 && param->p_velocity_x < 0)))
	{
		if (param->p_velocity_x > 0)
			param->p_velocity_x -= precision;
		else if (param->p_velocity_x < 0)
			param->p_velocity_x += precision;
	}
	if (velocity_x > 0 && param->p_velocity_x < 0 || velocity_x < 0 && param->p_velocity_x > 0)
		param->p_velocity_x = 0;
	param->px += param->p_velocity_x;
}

void		adjust_velocity_y(t_complete *param)
{
	const bool		velocity_y = param->p_velocity_y > 0;
	const float		precision = 0.5;

	while((check_collision(param, &(t_hitbox){param->py + param->p_velocity_y, param->py, 32, 32})
		&& ((velocity_y > 0 && param->p_velocity_y > 0)) || (velocity_y < 0 && param->p_velocity_y < 0)))
	{
		if (param->p_velocity_y > 0)
			param->p_velocity_y -= precision;
		else if (param->p_velocity_y < 0)
			param->p_velocity_y += precision;
	}
	if (velocity_y > 0 && param->p_velocity_y < 0 || velocity_y < 0 && param->p_velocity_y > 0)
		param->p_velocity_y = 0;
	param->py += param->p_velocity_y;
}

void		character_moves(t_complete *param)
{
	adjust_velocity_x(param);
	adjust_velocity_y(param);
	param->p_velocity_x = 3 * (param->keys[XK_d] - param->keys[XK_a]);
	param->p_velocity_y = 3 * (param->keys[XK_s] - param->keys[XK_w]);
	if(param->keys[XK_d])
		param->p_flipped = false;
	else if(param->keys[XK_a])
		param->p_flipped = true;
}

// Boucle hook
int on_update(t_complete *param, t_frames *char_frames)
{
	printf("vx: %f\n", param->p_velocity_x);
	printf("vy: %f\n", param->p_velocity_y);
	character_moves(param);
	clear_screen(param->img, 0x00000000);
	draw_map(param, param->map);
	ft_draw_sprite(param, param->player_frames[param->current_frame], param->px, param->py, param->p_flipped);
	mlx_put_image_to_window(param->mlx, param->win, param->img, 0, 0);

	if (getms() - param->last_frame_time > 200)
	{
		param->last_frame_time = getms();
		param->current_frame++;
		if (param->current_frame >= 4)
			param->current_frame = 0;
	}
	// switch_frames(char_frames);
	return (0);
}

// void	switch_frames(t_frames *frames)
// {
// 	if (getms() - frames->last_frame_time > 200)
// 	{
// 		frames->last_frame_time = getms();
// 		frames->current_frame++;
// 		if (frames->current_frame >= frames->number_of_frames)
// 			frames->current_frame = 0;
// 	}
// }

// void	*change_frame(t_complete *param)
// {
// 	int		numFrames;

// 	numFrames = 4;
// 	param->player = load_xpm_image(&param, "./sprites/character/passive/robot_neutral.xpm");
// 	return param->player;
// }

int main(void)
{
	t_complete	s;
	t_frames	char_frames;

	if(initialisation(&s))
		return(write(1, "fail", 4), 0);
	affectation(&s);
	mlx_put_image_to_window(s.mlx, s.win, s.img, 0, 0);
	character_animated(&s);
	collectible_animated(&s);
	char_frames.number_of_frames = 4;
	char_frames.current_frame = 0;
	char_frames.last_frame_time = 0;
	char_frames.interval = 200;

	// boucle de jeu
	mlx_do_key_autorepeatoff(s.mlx);
	mlx_loop_hook(s.mlx, on_update, &s);
	mlx_hook(s.win, KeyPress, KeyPressMask, key_pressed_hook, &s);
	mlx_hook(s.win, KeyRelease, KeyReleaseMask, key_released_hook, &s);
	mlx_hook(s.win, DestroyNotify, 0, close_hook, &s);
	mlx_loop(s.mlx);
	mlx_do_key_autorepeaton(s.mlx);

	if(s.win == NULL)
	{
		mlx_clear_window(s.mlx, s.win);
		mlx_destroy_window(s.mlx, s.win);
		free(s.mlx);
		// return (MALLOC_ERROR);
	}
	return (0);
}
