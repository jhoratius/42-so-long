/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:07:00 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/27 18:25:24 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/so_long.h"

void	check_path_cbles(t_complete *s, char **map, int x, int y, int jump)
{
	int	max_jump;

	max_jump = 1;
	if(x < 0 || y < 0 || x >= s->map_width || y >= s->map_height)
		return ;
	if(map[y][x] == '1' || map[y][x] == '.')
		return ;
	if(map[y][x] == 'C')
	{
		if((map[y + 1][x] == '1') && (map[y - 1][x] == '1')
		&& (map[y][x + 1] == '1') && (map[y][x - 1] == '1'))
		{
			map[y][x] = '.';
			return ;
		}
		s->c_count2++;
	}
	if(map[y][x] == 'E' || map[y][x] == 'P')
	{
		find_path_cbles(s, map, x, y, jump);
		return ;
	}
	map[y][x] = '.';
	find_path_cbles(s, map, x, y, jump);
	return ;
}

int	find_path_cbles(t_complete *s, char **map, int x, int y, int jump)
{
	if(jump <= 0)
	{
		check_path_cbles(s, map, x + 1, y, 0);
		check_path_cbles(s, map, x - 1, y, 0);
		check_path_cbles(s, map, x, y + 1, 0);
		check_path_cbles(s, map, x, y - 1, jump - 1);
		check_path_cbles(s, map, x + 1, y + 1, 0);
		check_path_cbles(s, map, x - 1, y - 1, 0);
	}
	else
	{
		check_path_cbles(s, map, x + 1, y - 1, jump - 1);
		check_path_cbles(s, map, x - 1, y + 1, 0);
	}
	return (0);
}

void	check_path_exit(t_complete *s, char **map, int x, int y, int jump)
{
	if(x < 0 || y < 0 || x >= s->map_width || y >= s->map_height)
		return ;
	if(map[y][x] == '1' || map[y][x] == '-')
		return ;
	if(map[y][x] == 'E')
	{
		if((map[y + 1][x] == '1') && (map[y - 1][x] == '1')
		&& (map[y][x + 1] == '1') && (map[y][x - 1] == '1'))
		{
			map[y][x] = '-';
			return ;
		}
		s->e_count2++;
	}
	map[y][x] = '-';
	find_path_exit(s, map, x, y, jump);
	return ;
}

int	find_path_exit(t_complete *s, char **map, int x, int y, int jump)
{
	if(jump <= 0)
	{
		check_path_exit(s, map, x + 1, y, 0);
		check_path_exit(s, map, x - 1, y, 0);
		check_path_exit(s, map, x, y + 1, 0);
		check_path_exit(s, map, x, y - 1, 0);
		check_path_exit(s, map, x + 1, y + 1, 0);
		check_path_exit(s, map, x - 1, y - 1, 0);
	}
	else
	{
		check_path_exit(s, map, x + 1, y - 1, jump - 1);
		check_path_exit(s, map, x - 1, y + 1, 0);
	}
	return (0);
}

int	check_paths(t_complete *s)
{
	int i = -1;
	get_p_pos(s);
	printf("ppx: %d, ppy: %d\n", s->ppx, s->ppy);
	find_path_cbles(s, s->map_copy, s->ppx, s->ppy, 0);
	printf("c_count : %d\n", s->c_count);
	printf("c_count2: %d\n", s->c_count2);
	while(s->map_copy[++i])
		printf("%s", s->map_copy[i]);
	printf("\n");
	if (s->c_count2 == s->c_count)
		write(1, "All collectables are reachable\n", 32);
	else
	{
		write(1, "Some collectables are not reachable\n", 36);
		return (check_leaks(s), 0);
	}

	i = -1;
	find_path_exit(s, s->map_copy, s->ppx, s->ppy, 0);
	printf("e_count : %d\n", s->e_count);
	printf("e_count2: %d\n", s->e_count2);
	while(s->map_copy[++i])
		printf("%s", s->map_copy[i]);
	printf("\n");
	if(s->e_count2 == s->e_count)
		write(1, "Exit is reachable\n", 19);
	else
	{
		write(1, "Exit is not reachable\n", 23);
		return (check_leaks(s), 0);
	}
	return (1);
}
