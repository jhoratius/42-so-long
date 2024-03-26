/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:14:47 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/26 18:07:18 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	parse_map(t_complete *s)
{
	int	x;
	int	y;

	y = 0;
	if (!mandatory_map(s))
		return (write(1, "Map need changes\n", 1), check_leaks(s), 0);
	while (s->map[y])
	{
		x = 0;
		if (check_length(s, y))
			return (check_leaks(s), 0);
		while (s->map[y][x])
		{
			if (parse_walls(s, y, x))
			{
				write(1, "Map is not surrounded by walls\n", 37);
				return (check_leaks(s), 0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	parse_walls(t_complete *s, int y, int x)
{
	if ((y == 0) && ((s->map[y][x] != '1' && s->map[y][x] != '\n')))
		return (1);
	if ((x == 0) && ((s->map[y][x] != '1')))
		return (1);
	if ((y == s->map_height - 1)
		&& ((s->map[y][x] != '1' && s->map[y][x] != '\n')))
		return (1);
	if ((x == s->map_width - 2)
		&& ((s->map[y][x] != '1' && s->map[y][x] != '\n')))
		return (1);
	return (0);
}

int	check_length(t_complete *s, int y)
{
	if (y == s->map_height - 1)
	{
		if (ft_strlen(s->map[y]) != s->map_width - 1)
			return (write(1, "Map is not rectangular\n", 24), 1);
	}
	else
	{
		if (ft_strlen(s->map[y]) != s->map_width)
			return (write(1, "Map is not rectangular\n", 24), 1);
	}
	if (ft_strlen(s->map[y]) < 3 || ft_strlen(s->map[y]) > 25)
		return (write(1, "Map has not the proper length requisites\n", 42), 1);
	return (0);
}

int	mandatory_map(t_complete *s)
{
	int			x;
	int			y;

	y = 0;
	while (s->map[y])
	{
		x = 0;
		while (s->map[y][x] != '\0')
		{
			if (s->map[y][x] == 'C')
				s->c_count++;
			if (s->map[y][x] == 'E')
				s->e_count++;
			if (s->map[y][x] == 'P')
				s->p_count++;
			x++;
		}
		y++;
	}
	if (s->p_count != 1 || s->e_count != 1)
		return (write(1, "Map need one P or one E\n", 24), 0);
	if (s->c_count < 1)
		return (write(1, "Map need at least one C\n", 24), 0);
	return (1);
}

// int	check_path(t_complete *s)
// {
// 	int		x;
// 	int		y;

// 	x = 1;
// 	while (x < s->map_height - 1)
// 	{
// 		y = 1;
// 		while (y < s->map_width - 2)
// 			y++;
// 		x++;
// 	}
// 	return (0);
// }
