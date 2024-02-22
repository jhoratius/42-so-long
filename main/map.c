/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:06:31 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/02/22 16:55:06 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	launch_game(char *map_file)
{
	char **map = load_map(map_file);
	if(!map)
		return ;
}

char	**load_map(char *file)
{
	int		fd;
	char	**map;
	char	*str;
	int		i;
	
	i = 0;
	fd = open(file, O_RDWR);
	if (fd == -1)
		return (0);
	map = (char **)malloc(10 * sizeof(char *));
	if (!map)
		return (NULL);
	while (get_next_line(fd, (void *) &str) > 0)
	{
		map[i] = str;
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

void	draw_map(t_complete *complete, char **map)
{
	int			x;
	int			y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == '0' || map[y][x] == 'P')
				ft_draw_sprite(complete, complete->floor, x * 32 * SCALE, y * 32 * SCALE, false);
			if (map[y][x] == '1')
				ft_draw_sprite(complete, complete->barrier, x * 32 * SCALE, y * 32 * SCALE, false);
			if (map[y][x] == 'C')
			{
				ft_draw_sprite(complete, complete->floor, x * 32 * SCALE, y * 32 * SCALE, false);
				complete->cx[complete->collectables] = x;
				complete->cy[complete->collectables] = y;
				complete->collectables++;
			}
				// ft_draw_sprite(complete, complete->floor, x * 32 * SCALE, y * 32 * SCALE, false);
			if (map[y][x] == 'E')
				ft_draw_sprite(complete, complete->floor, x * 32 * SCALE, y * 32 * SCALE, false);
			x++;
		}
		y++;
	}
	return ;
}

bool	collide(t_hitbox rect1, t_hitbox rect2, char c)
{
	// float	distance_x;
	// float	distance_y;
	float	distance;

	// distance_x = 0;
	// distance_y = 0;
	// if(c == 'x')
		// distance_x = fabs(rect1.x - rect2.x);
		return (rect1.x < rect2.x + rect2.width && rect1.x + rect1.width > rect2.x && rect1.y < rect2.y + rect2.height && rect1.height + rect1.y > rect2.y);
	// if(c == 'y')
		// distance_y = fabs(rect1.y - rect2.y);
		// return (distance_y < rect1.height / 2 + rect2.height / 2);
	
}

int		check_collision(t_complete *game)
{
	int			x;
	int			y;
	t_hitbox	player_hitbox;
	t_hitbox	map_hitbox;

	player_hitbox.x = game->px + game->p_velocity_x + 11 * SCALE;
	player_hitbox.y = game->py + game->p_velocity_y + 10 * SCALE;
	player_hitbox.width = 20 * SCALE - 24;
	player_hitbox.height = 21 * SCALE;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x] != '\0')
		{
			if (game->map[y][x] == '1')
			{
				map_hitbox.x = x * 32 * SCALE;
				map_hitbox.y = y * 32 * SCALE;
				map_hitbox.width = 32 * SCALE;
				map_hitbox.height = 32 * SCALE;
				if (collide(player_hitbox, map_hitbox, x))
					return (1);
				if (collide(player_hitbox, map_hitbox, y))
					return (2);
			}
			x++;
		}
		y++;
	}
	return (false);
}

// float	