/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:07:00 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/26 18:55:49 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/so_long.h"

int	check_path(t_complete *s, char **map, int x, int y, int jump)
{
	int	max_jump;

	max_jump = 1;
	if(x < 0 || y < 0 || x >= s->map_width || y >= s->map_height)
		return (0);
	if(map[y][x] == '1' || map[y][x] == '.'
		|| map[y][x] == 'E' || map[y][x] == 'C')
		return (0);
	map[y][x] = '.';
	find_path(s, map, x, y, jump);
}

int	find_path(t_complete *s, char **map, int x, int y, int jump)
{
	if(jump <= 0)
	{
		check_path(s, map, x + 1, y, 0);
		check_path(s, map, x - 1, y, 0);
		check_path(s, map, x, y + 1, 0);
		check_path(s, map, x, y - 1, jump - 1);
		check_path(s, map, x + 1, y + 1, 0);
		check_path(s, map, x - 1, y - 1, 0);
	}
	else
	{
		check_path(s, map, x + 1, y - 1, jump - 1);
		check_path(s, map, x - 1, y + 1, 0);
	}
	return (0);
}
