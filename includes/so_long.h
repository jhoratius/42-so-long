/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:05:52 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/15 15:20:01 by jhoratiu         ###   ########.fr       */
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

	float			p_velocity_x;
	float			p_velocity_y;
	int				life_points;

	bool			p_flip;
	bool			atk_flip;
	bool			en_flip;

	bool			running;
	bool			p_atk;
	bool			en_attack;
	bool			end_attack;
	bool			atk_launched;
	bool			hit;
	bool			has_jumped;
	bool			open_exit;
	bool			end_game;
	bool			lose_game;
	bool			keys[65535];

	t_img			*player_f[4];
	int				p_curr_f;
	suseconds_t		p_last_f_t;

	t_img			*p_run_f[5];
	int				pr_curr_f;
	suseconds_t		pr_last_f_t;

	t_img			*collect_f[4];
	int				c_curr_f;
	suseconds_t		c_last_f_t;

	t_img			*exit_f[4];
	int				e_curr_f;
	suseconds_t		e_last_f_t;

	t_img			*enemy_f[4];
	int				en_curr_f;
	suseconds_t		en_last_f_t;

	t_img			*atk_enemy_f[3];
	int				en_atk_curr_f;
	suseconds_t		en_atk_last_f_t;

	t_img			*atk_unit_f[4];
	int				atk_u_curr_f;
	suseconds_t		unite_atk_last_f_t;

	suseconds_t		last_attack_frame;

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

// banner
// void				banner_choice(t_complete *param);

// character
void				adjust_velocity_x(t_complete *game, float vx);
void				adjust_velocity_y(t_complete *game, float vy);
void				character_moves(t_complete *param);
void				atk_unite(t_complete *param);

// collectible
void				affectation_collect(t_complete *s);
void				get_c_pos(t_complete *param);

// display
void				display_megaman();

// draws
void				ft_draws1(t_complete *s);
void				ft_draws2(t_complete *s);

// enemy
void				get_enemy_pos(t_complete *s);
void				enemy_animated(t_complete *param);
void				follow_entity(t_complete *s);
void				detect_entity(t_complete *s);

// frames
void				time_frames(suseconds_t *last_fr_t, int *c_frame, int n_frames, int time);
void				time_frames_p_atk(t_complete *s, int *c_frame, int n_frames, int time);
void				time_frames_exit(t_complete *s, int *c_frame, int n_frames, int time);
void				time_frames_en_atk(t_complete *s, int *c_frame, int n_frames, int time);
void				all_frames(t_complete *s);

// atk
void				follow_entity_a(t_complete *s, int px, int py);
void				attack_collision(t_complete *s);
void				attack_u_collision(t_complete *s);
void				attack_entity(t_complete *s);

// exit
void				exit_animated(t_complete *param);

// free
void				check_free(t_complete *s);
void				free_pointers(void *ptr);
void				check_sprites(t_complete *s);
void				destroy_sprites(t_complete *s, t_img *img, int n);
void				check_leaks(t_complete *s);

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
void				affectation_frames(t_complete *s);

// init 2
void				init_hitboxs(t_complete *s);

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

// utils
suseconds_t			getms(void);

#endif
