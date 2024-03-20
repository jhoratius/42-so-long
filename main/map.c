/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:06:31 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/20 14:28:55 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int		count_map_line(char *map_file)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(map_file, O_RDWR);
	if (fd == -1)
		return (0);
	while (get_next_line(fd, (void *) &line) > 0)
	{
		i++;
		free(line);
	}
	close(fd);
	return (i);
}

char	**load_map(t_complete *s, char *file)
{
	int		fd;
	char	**map;
	char	*str;
	int		i;

	i = 0;
	fd = open(file, O_RDWR);
	if (fd == -1)
		return (0);
	map = (char **)malloc((count_map_line(file)+1) * sizeof(char *));
	if (!map)
		return (NULL);
	while (get_next_line(fd, (void *) &str) > 0)
	{
		map[i] = str;
		i++;
	}
	s->map_width = ft_strlen(map[0]);
	map[i] = NULL;
	close(fd);
	return (map);
}

void	draw_map(t_complete *s, char **map)
{
	int			x;
	int			y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == '0' || map[y][x] == 'P' || map[y][x] == 'A')
				ft_draw_sprite(s, s->floor, x * 32 * SCALE, y * 32 * SCALE, false);
			if (map[y][x] == '1')
				ft_draw_sprite(s, s->barrier, x * 32 * SCALE, y * 32 * SCALE, false);
			if (map[y][x] == 'C')
				ft_draw_sprite(s, s->floor, x * 32 * SCALE, y * 32 * SCALE, false);
			if (map[y][x] == 'E')
				ft_draw_sprite(s, s->floor, x * 32 * SCALE, y * 32 * SCALE, false);
			x++;
		}
		y++;
	}
	return ;
}

int		check_collision(t_complete *s)
{
	int			x;
	int			y;
	t_hitbox	player_hitbox;
	t_hitbox	map_hitbox;

	player_hitbox.x = s->px + s->p_velocity_x + 11 * SCALE;
	player_hitbox.y = s->py + s->p_velocity_y + 10 * SCALE;
	player_hitbox.width = 20 * SCALE - 24;
	player_hitbox.height = 21 * SCALE;
	y = 0;
	while (s->map[y])
	{
		x = 0;
		while (s->map[y][x] != '\0')
		{
			if (s->map[y][x] == '1')
			{
				map_hitbox.x = x * 32 * SCALE;
				map_hitbox.y = y * 32 * SCALE;
				map_hitbox.width = 32 * SCALE;
				map_hitbox.height = 32 * SCALE;
				if (collide(player_hitbox, map_hitbox))
					return (1);
				if (collide(player_hitbox, map_hitbox))
					return (2);
			}
			x++;
		}
		y++;
	}
	return (false);
}

// float	