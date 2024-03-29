/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:05:52 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/29 18:14:45 by jhoratiu         ###   ########.fr       */
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
# define WIN_WIDTH 1920
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

typedef struct s_complete
{
	int				fd;
	int				heightmap;
	int				widthmap;
	int				collectables;
	char			**map;
	char			**map_copy;

	void			*floor;
	void			*barrier;
	void			*player;
	void			*enemy;
	void			*exit;
	void			*collectable;
	void			*collectible_count;
	void			*exit_banner;
	void			*mlx;
	void			*win;
	t_img			*img;

	int				px;
	int				py;
	int				ppx;
	int				ppy;
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
	int				map_height;
	int				p_count;
	int				c_count;
	int				e_count;
	int				c_count2;
	int				e_count2;
	int				path_jump;

	float			p_velocity_x;
	float			p_velocity_y;

	bool			p_flip;
	bool			en_flip;

	bool			running;
	bool			jumped;
	bool			open_exit;
	bool			end_game;
	bool			lose_game;
	bool			keys[65535];

	t_hitbox		p_hbox;
	t_hitbox		c_hbox;
	t_hitbox		w_hbox;

}	t_complete;

// animation
void				all_affectations(t_complete *param);
void				character_animated(t_complete *param);
void				collectible_animated(t_complete *param);

// character
void				adjust_velocity_x(t_complete *game, float vx);
void				adjust_velocity_y(t_complete *game, float vy);
void				character_moves(t_complete *param);
void				get_p_pos(t_complete *s);
void				update_hb_p(t_complete *s);

// collectible
void				affectation_collect(t_complete *s);
void				get_c_pos(t_complete *param);
void				collect_a_unit(t_complete *param, t_hitbox player, t_hitbox item);
void				change_map_values(t_complete *game, int k);

// display
void				display_megaman();

// draws
void				ft_draws1(t_complete *s);

// exit
void				enter_exit(t_complete *s);
void				get_e_pos(t_complete *s);

// free
void				check_free(t_complete *s);
void				check_sprites(t_complete *s);
void				destroy_sprite(t_complete *s, t_img *img);
void				check_leaks(t_complete *s);
void				free_map(t_complete *s);
void				free_copy_map(t_complete *s);

// graphic
unsigned int		get_pixel(t_img *img, int x, int y, bool flipped);
void				clear_screen(t_img *img, unsigned int color);
void				*load_xpm_image(t_complete *param, char *imagePath);
void				ft_draw_sprite(t_complete *game, t_img *img, int x, int y);
bool				collide(t_hitbox rect1, t_hitbox rect2);

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
int					count_map_line(char *map_file);
char				**load_map(t_complete *s, char *file);
void				draw_map(t_complete *complete, char **map);
int					check_collision(t_complete *s, t_hitbox map_hb);
t_hitbox			fill_hitbox(int x, int y, int width, int height);

// map parsing
int					parse_map(t_complete *s);
int					parse_walls(t_complete *s, int x, int y);
int					check_length(t_complete *s, int y);
int					small_map(t_complete *s);
int					mandatory_map(t_complete *s);

// pathfinding
void				check_path_cbles(t_complete *s, int x, int y, int jump);
void				find_path_cbles(t_complete *s, int x, int y, int jump);
void				check_path_exit(t_complete *s, int x, int y, int jump);
void				find_path_exit(t_complete *s, int x, int y, int jump);
int					check_paths(t_complete *s);

// pathfinding_jump
int					check_jumps(t_complete *s, int x, int y, int jump);
int					find_path_jump_c(t_complete *s, char **map);
int					check_wall_range(t_complete *s, int x, int y, int i);

// so long
int					on_update(t_complete *param);

// utils
int					ft_strlen(char *str);
#endif
