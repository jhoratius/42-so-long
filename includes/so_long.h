/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:05:52 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/02/15 14:51:12 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// libmlx.dylib
#ifndef SO_LONG
# define SO_LONG
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <bsd/string.h>
# include <stdio.h>
# include <ctype.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>

//# include "./includes/mlx.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "get_next_line.h"
# include "ftprintf.h"

# define SCALE 2.5
// # define NUM_FRAMES 4
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

typedef struct s_complete
{
	int		fd;
	int		heightmap;
	int		widthmap;
	int		playercount;
	int		columncount;
	int		exitcount;
	int		x_axis;
	int		y_axis;
	int		counterl;
	int		collectables;

	char	**map;

	void	*floor;
	void	*barrier;
	void	*player;
	void	*exit;
	void	*collectable;
	void	*mlx;
	void	*win;
	t_img	*img;

	t_img	*player_frames[4];
	t_img	*collect_frames[2];
	int		current_frame;
	suseconds_t		last_frame_time;

	int		px;
	int		py;
	int		cx;
	int		cy;
	float	p_velocity_x;
	float	p_velocity_y;
	bool	p_flipped;
	float	p_speed;

	bool	keys[65535];
}	t_complete;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_hitbox
{
	int	x;
	int	y;
	int	width;
	int	height;
}				t_hitbox;

typedef struct s_frames
{
	t_img			player_frames[4];
	int				number_of_frames;
	int				current_frame;
	suseconds_t		last_frame_time;
	suseconds_t		interval;
}				t_frames;

int		initialisation(t_complete *s);
void	affectation(t_complete *s);
int		exit_point(t_complete *game);
int		map_reading(t_complete *game, char **argv);
int		controls_working(int command, t_complete *game);
void	adding_in_graphics(t_complete game);
void	place_images_in_games(t_complete *game);
void	check_errors(t_complete game);

void	put_empty(char *str, int i);
void	put_walls(char *str, int i);
void	put_collectibles(char *str, int i);
void	put_character(char *str, int i);
void	put_exit(char *str, int i);

char	**load_map(char *file);
void	draw_map(t_complete *complete, char **map);
void	ft_draw_sprite(t_complete *game, t_img *img, int x, int y, bool flipped);
void	character_moves(t_complete *param);
bool	check_collision(t_complete *game, t_hitbox *map_hitbox);

void	*load_xpm_image(t_complete *param, char *imagePath);
void	launch_game(char *map_file);
void	load_frame(t_complete *param);
void	character_animated(t_complete *param);
void	switch_frames(t_frames *frames);
suseconds_t	getms(void);

// hooks
int	key_released_hook(int keycode, t_complete *param);
int	close_hook(t_complete *param);
int	key_pressed_hook(int keycode, t_complete *param);

#endif