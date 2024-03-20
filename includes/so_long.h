/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:05:52 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/20 16:56:41 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <bsd/string.h>
# include <stdio.h>
# include <ctype.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>
# include <math.h>

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "get_next_line.h"
# include "ftprintf.h"

# define SCALE 2.5
# define WIN_WIDTH 1780
# define WIN_HEIGHT 720
# define M_PI 3.14159265358979323846

# define BLUE "\x1b[0;34m"
# define BLUE_LIGHT "\x1b[0;94m"
# define WHITE "\x1b[0;37m"

// Structures

typedef struct s_hitbox
{
	int	x;
	int	y;
	int	width;
	int	height;
}				t_hitbox;

typedef struct s_frames
{
	t_img			*frames;
	int				number_of_frames;
	int				current_frame;
	suseconds_t		last_frame_time;
	suseconds_t		interval;
}				t_frames;

typedef struct s_complete
{
	int				fd;
	int				heightmap;
	int				widthmap;
	int				collectables;
	char			**map;

	void			*floor;
	void			*barrier;
	void			*player;
	void			*enemy;
	void			*e_attack;
	void			*exit;
	void			*collectable;
	void			*collectible_count;
	void			*exit_banner;
	void			*lose_banner;
	void			*mlx;
	void			*win;
	t_img			*img;

	int				px;
	int				py;
	int				ex;
	int				ey;
	int				cx[100];
	int				cy[100];
	int				collected[100];
	int				ax[3];
	int				ay[3];
	int				uax[3];
	int				uay[3];
	float			dir_x[3];
	float			dir_y[3];
	int				dest_x[3];
	int				dest_y[3];
	int				enx;
	int				eny;
	int				map_width;

	float			p_velocity_x;
	float			p_velocity_y;
	int				life_points;

	bool			p_flip;
	bool			atk_flip;
	bool			en_flip;

	bool			running;
	bool			p_atk;
	bool			atk_launched;
	bool			has_jumped;
	bool			open_exit;
	bool			end_game;
	bool			lose_game;
	bool			keys[65535];

	t_hitbox		p_hbox;
	t_hitbox		c_hbox;
	t_hitbox		ex_hbox;
	t_hitbox		e_atk_hbox;
	t_hitbox		p_atk_hbox;

}	t_complete;

// animation
void				all_affectations(t_complete *param);
void				character_animated(t_complete *param);
void				collectible_animated(t_complete *param);

// character
void				adjust_velocity_x(t_complete *game, float vx);
void				adjust_velocity_y(t_complete *game, float vy);
void				character_moves(t_complete *param);

// collectible
void				affectation_collect(t_complete *s);
void				get_c_pos(t_complete *param);
int					collect_a_unit(t_complete *param);

// display
void				display_megaman();

// draws
void				ft_draws1(t_complete *s);

// exit
void				enter_exit(t_complete *s);

// free
void				check_free(t_complete *s);
void				check_sprites(t_complete *s);
void				destroy_sprite(t_complete *s, t_img *img);
void				check_leaks(t_complete *s);
void				free_map(t_complete *s);

// graphic
unsigned int		get_pixel(t_img *img, int x, int y, bool flipped);
void				clear_screen(t_img *img, unsigned int color);
void				*load_xpm_image(t_complete *param, char *imagePath);
void				ft_draw_sprite(t_complete *game, t_img *img, int x, int y, bool flipped);

// hooks
int					key_released_hook(int keycode, t_complete *param);
int					close_hook(t_complete *param);
int					key_pressed_hook(int keycode, t_complete *param);

// init
int					initialisation(t_complete *s);
void				affectation_values(t_complete *s);
void				affectation_sprites(t_complete *s);

// init 2
void				init_hitboxs(t_complete *s);

// map
char				**load_map(t_complete *s, char *file);
void				draw_map(t_complete *complete, char **map);
bool				collide(t_hitbox rect1, t_hitbox rect2);
int					check_collision(t_complete *game);
void				change_map_values(t_complete *game, int i, int j, int k);
int					count_map_line(char *map_file);

// map parsing
void				parse_map(t_complete *s);

// so long
int					on_update(t_complete *param);

// utils
int					ft_strlen(char *str);
#endif
