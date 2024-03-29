/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_jump.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:43:57 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/29 18:25:01 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	find_path_jump_c(t_complete *s, char **map)
{
	int	x;
	int	y;

	y = -1;
	while (s->map_copy[++y])
	{
		x = -1;
		while (s->map_copy[y][++x])
		{
			if (s->map_copy[y][x] == 'X')
			{
				if (!(check_jumps(s, x, y, 1)))
				{
					write(1, "Collectable not accessible\n", 28);
					return (0);
				}
			}	
		}
	}
	return (1);
}

int	check_jumps(t_complete *s, int x, int y, int jump)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(1)
	{
		if(s->map[y + i][x] == '1')
			break ;
		i++;
	}
	while(j <= 2)
	{
		// printf("y + i : %d, x + j : %d\n", y + i, x + j);
		// printf("y + i : %d, x - j : %d\n", y + i, x - j);
		if(s->map[y + i][x + j] == '1')
			break ;
		if(s->map[y + i][x - j] == '1')
			break ;
		j++;
		if(j == 3)
			j = -1;
	}
	i -= 1;
	// printf("y : %d, x : %d\n", y, x);
	// printf("i : %d\n", i);
	if (i > 1)
		return (0);
	if (j == -1)
		return (0);
	i++;
	// if (!(check_wall_range(s, x, y, i)))
	// 	return (0);
	// printf("i : %d\n", i - 1);
	return (1);
}

int	check_wall_range(t_complete *s, int x, int y, int i)
{
	int	j;
	int	reached;

	j = 0;
	reached = 0;
	// printf("x  : %d\n", x);
	// printf("mw - 4 : %d\n", s->map_width - 4);
	// printf("mh - 4 : %d\n", s->map_height - 4);
	// printf("\n");
	if(x <= 2 || x >= s->map_width - 4)
		reached = 1;
	if(y >= s->map_height - 4)
		reached = 1;
	if(reached == 1)
		return (1);
	return (0);
}
