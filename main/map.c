/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:06:31 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/30 17:47:27 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	count_map_line(char *map_file)
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
	if (fd == -1 || count_map_line(file) < 3)
	{
		write(1, "Map file error\n", 16);
		return (0);
	}
	map = (char **)malloc((count_map_line(file)+1) * sizeof(char *));
	if (!map)
		return (NULL);
	while (get_next_line(fd, (void *) &str) > 0)
	{
		map[i] = str;
		i++;
	}
	s->map_width = ft_strlen(map[0]);
	s->map_height = i;
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
				ft_draw_sprite(s, s->floor, x * 32 * SCALE, y * 32 * SCALE);
			if (map[y][x] == '1')
				ft_draw_sprite(s, s->barrier, x * 32 * SCALE, y * 32 * SCALE);
			if (map[y][x] == 'C')
				ft_draw_sprite(s, s->floor, x * 32 * SCALE, y * 32 * SCALE);
			if (map[y][x] == 'E')
				ft_draw_sprite(s, s->floor, x * 32 * SCALE, y * 32 * SCALE);
			x++;
		}
		y++;
	}
	return ;
}

int	check_collision(t_complete *s, t_hitbox map_hb)
{
	int			x;
	int			y;
	t_hitbox	player_hitbox;

	player_hitbox.x = s->px + s->p_velocity_x + 11 * SCALE;
	player_hitbox.y = s->py + s->p_velocity_y + 10 * SCALE;
	player_hitbox.width = 20 * SCALE - 24;
	player_hitbox.height = 21 * SCALE;
	y = -1;
	while (s->map[++y])
	{
		x = -1;
		while (s->map[y][++x] != '\0')
		{
			if (s->map[y][x] == '1')
			{
				map_hb = fill_hitbox(x * 32 * SCALE, y * 32 * SCALE,
					32 * SCALE, 32 * SCALE);
				if (collide(player_hitbox, map_hb))
					return (1);
			}
		}
	}
	return (false);
}

t_hitbox	fill_hitbox(int x, int y, int width, int height)
{
	t_hitbox	hitbox;

	hitbox.x = x;
	hitbox.y = y;
	hitbox.width = width;
	hitbox.height = height;
	return (hitbox);
}
