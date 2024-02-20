/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:54:09 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/02/20 16:02:48 by jhoratiu         ###   ########.fr       */
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

void	adjust_velocity_x(t_complete *game, float vx)
{
	const float	precision = 0.5;
	const bool	vx_positive = vx > 0;
	bool		collide_x;

	collide_x = check_collision(game);
	while (((vx_positive && vx > 0) || (!vx_positive && vx < 0)) && collide_x)
	{
		if (vx_positive)
			vx -= precision;
		else if (!vx_positive)
			vx += precision;
	}
	if ((vx_positive && vx < 0) || (!vx_positive && vx > 0))
		vx = 0;
	game->px += vx;
}

void		adjust_velocity_y(t_complete *game, float vy)
{
	const float	precision = 0.5;
	const bool	vy_positive = vy > 0;
	float 		p_vy = game->p_velocity_y;
	bool		collide_y;

	collide_y = check_collision(game);
	while (collide_y && abs(game->p_velocity_y) > precision)
	{
		if (vy_positive)
			game->p_velocity_y -= precision;
		else if (!vy_positive)
			game->p_velocity_y += precision;
		// collide_y = check_collision(game);
	}
	vy = game->p_velocity_y;
	game->p_velocity_y = p_vy;
	if (collide_y)
	{
		vy = 0;
		game->p_velocity_y = 0;
	}
	game->py += vy;
}

void		character_moves(t_complete *param)
{
	bool		collision;

	collision = check_collision(param);
	param->p_velocity_x = 3 * (param->keys[XK_d] - param->keys[XK_a]);
	// param->p_velocity_y = 3 * (param->keys[XK_s] - param->keys[XK_w]);
	if (param->keys[XK_w] && fabs(param->p_velocity_y < 0.5) && !param->has_jumped)
	{
		param->p_velocity_y = -5;
		param->has_jumped = true;
	}
	if(collision && param->has_jumped)
		param->has_jumped = false;
	// else
	param->p_velocity_y += 9.81 * 0.016;
	if (param->keys[XK_d] - param->keys[XK_a])
		param->p_flipped = (param->keys[XK_d] - param->keys[XK_a]) < 0;
	adjust_velocity_x(param, param->p_velocity_x);
	adjust_velocity_y(param, param->p_velocity_y);
}

// Boucle hook
int on_update(t_complete *param, t_frames *char_frames)
{
	printf("vx: %f\n", param->p_velocity_x);
	printf("vy: %f\n", param->p_velocity_y);
	printf("px: %d\n", param->px);
	printf("py: %d\n", param->py);
	printf("jmp: %d\n", param->has_jumped);
	character_moves(param);
	clear_screen(param->img, 0x00000000);
	draw_map(param, param->map);
	ft_draw_sprite(param, param->player_frames[param->p_current_frame], param->px, param->py, param->p_flipped);
	ft_draw_sprite(param, param->collect_frames[param->c_current_frame], param->cx, param->cy, false);
	mlx_put_image_to_window(param->mlx, param->win, param->img, 0, 0);

	if (getms() - param->p_last_frame_time > 200)
	{
		param->p_last_frame_time = getms();
		param->p_current_frame++;
		if (param->p_current_frame >= 4)
			param->p_current_frame = 0;
	}

	if (getms() - param->c_last_frame_time > 400)
	{
		param->c_last_frame_time = getms();
		param->c_current_frame++;
		if (param->c_current_frame >= 4)
			param->c_current_frame = 0;
	}
	// switch_frames(char_frames);
	return (0);
}

// void	switch_frames(t_frames *frames)
// {t
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

void	free_init(t_complete *s)
{
	free(s->mlx);
	free(s->win);
	free(s->img);
}

void	free_affectation(t_complete *s)
{
	free(s->collectable);
	free(s->floor);
	free(s->barrier);
	free(s->player);
	free(s->exit);
	free(s->px);
	free(s->py);
	free(s->cx);
	free(s->cy);
	free(s->collectable);
	free(s->floor);
	free(s->barrier);
	free(s->player);
	free(s->p_current_frame);
	free(s->p_last_frame_time);
	free(s->c_current_frame);
	free(s->c_last_frame_time);
	free(s->map);
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
