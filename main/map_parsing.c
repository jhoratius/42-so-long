/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:14:47 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/20 17:11:07 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	parse_map(t_complete *s)
{
	int	x;
	int	y;

	y = 0;
	while (s->map[y])
	{
		x = 0;
		while (s->map[y][x] != '\0')
		{
			// if (parse_walls(s, x, y))
				// write(1, "Error\nMap is not surrounded by walls\n", 37);
			x++;
		}
		y++;
	}
}

int		parse_walls(t_complete *s, int x, int y)
{
	if((y == 0 || y == s->heightmap - 1) && s->map[y][x] != 1)
		return (0);
	if((x == 0 || x == s->map_width - 1) && s->map[y][x] != 1)
		return (0);
	return (1);
}

