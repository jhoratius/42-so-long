/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:05:52 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/11 17:19:10 by jhoratiu         ###   ########.fr       */
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

// Structures
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

// typedef struct s_projectiles
// {
// 	int			x;
// 	int			y;
// 	int			width;
// 	int			height;
// 	int			dest_x;
// 	int			dest_y;
// 	bool		launched;
// 	bool		flipped;
// 	suseconds_t	last_frame_time;
// }			t_projectiles;

typedef struct s_frames
{
	t_img			player_frames[4];
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
	int				playercount;
	int				columncount;
	int				exitcount;
	int				x_axis;
	int				y_axis;
	int				counterl;
	int				collectables;
	bool			has_jumped;
	bool			open_exit;
	bool			end_game;

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
	void			*mlx;
	void			*win;
	t_img			*img;

	t_img			*player_frames[4];
	int				p_current_frame;
	suseconds_t		p_last_frame_time;

	t_img			*p_run_frames[5];
	int				pr_current_frame;
	suseconds_t		pr_last_frame_time;

	t_img			*collect_frames[4];
	int				c_current_frame;
	suseconds_t		c_last_frame_time;

	t_img			*exit_frames[4];
	int				e_current_frame;
	suseconds_t		e_last_frame_time;

	t_img			*enemy_frames[4];
	int				en_current_frame;
	suseconds_t		en_last_frame_time;

	t_img			*atk_enemy_frames[3];
	int				en_atk_current_frame;
	suseconds_t		en_atk_last_frame_time;

	t_hitbox		*p_hbox;
	t_hitbox		*c_hbox;

	// t_projectiles	*en_proj;

	int				px;
	int				py;
	int				cx[100];
	int				cy[100];
	int				collected[100];
	int				ex;
	int				ey;
	bool			en_flipped;
	bool			en_attack;
	bool			atk_launched;
	int				ax[3];
	int				ay[3];
	suseconds_t		last_attack_frame;
	int				dest_x[3];
	int				dest_y[3];
	bool			atk_flipped;
	int				enx;
	int				eny;
	float			p_velocity_x;
	float			p_velocity_y;
	bool			p_flipped;
	bool			running;
	float			p_speed;

	bool			keys[65535];
}	t_complete;

// animation
void				character_animated(t_complete *param);
void				collectible_animated(t_complete *param);

// character
void				adjust_velocity_x(t_complete *game, float vx);
void				adjust_velocity_y(t_complete *game, float vy);
void				character_moves(t_complete *param);

// collectible
void			affectation_collect(t_complete *s);
void				get_c_pos(t_complete *param);

// enemy
void				get_enemy_pos(t_complete *s);
void				enemy_animated(t_complete *param);
void				follow_entity(t_complete *s);
void				detect_entity(t_complete *s);
void				attack_entity(t_complete *s);

// atk
void				follow_entity_a(t_complete *s, int px, int py);

// exit
void				exit_animated(t_complete *param);
// void				load_banner(t_complete *s);

// free
void				free_init(t_complete *s);
void				free_affectation(t_complete *s);

// graphic
unsigned int		get_pixel(t_img *img, int x, int y, bool flipped);
void				clear_screen(t_img *img, unsigned int color);
void				*load_xpm_image(t_complete *param, char *imagePath);
void				ft_draw_sprite(t_complete *game, t_img *img, int x, int y, bool flipped);

// hitbox
// affect_hitboxs(t_complete *param);

// hooks
int					key_released_hook(int keycode, t_complete *param);
int					close_hook(t_complete *param);
int					key_pressed_hook(int keycode, t_complete *param);

// init
int					initialisation(t_complete *s);
void				affectation_values(t_complete *s);
void				affectation_sprites(t_complete *s);
void				affectation_frames(t_complete *s);

// map
void				launch_game(char *map_file);
char				**load_map(char *file);
void				draw_map(t_complete *complete, char **map);
bool				collide(t_hitbox rect1, t_hitbox rect2);
int					check_collision(t_complete *game);
void				change_map_values(t_complete *game, int i, int j, int k);

// main
int					exit_point(t_complete *game);
int					map_reading(t_complete *game, char **argv);
int					controls_working(int command, t_complete *game);
void				adding_in_graphics(t_complete game);
void				place_images_in_games(t_complete *game);
void				check_errors(t_complete game);

// so long
int					on_update(t_complete *param, t_frames *char_frames);
int					main(void);

// utils
suseconds_t			getms(void);

#endif
