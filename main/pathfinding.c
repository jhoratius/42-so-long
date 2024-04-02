/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:07:00 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/04/02 19:16:40 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	check_path_cbles(t_complete *s, int x, int y, int jump)
{
	if (x < 0 || y < 0 || x >= s->map_width || y >= s->map_height)
		return ;
	if (s->map_copy[y][x] == '1' || s->map_copy[y][x] == '.')
		return ;
	s->map_copy[y][x] = '.';
	if (s->map_copy[y][x] == 'C')
		s->c_count2++;
	if (s->map_copy[y][x] == 'E' || s->map_copy[y][x] == 'P')
	{
		find_path_cbles(s, x, y, jump);
	}
	
	find_path_cbles(s, x, y, jump);
	return ;
}

void	find_path_cbles(t_complete *s, int x, int y, int jump)
{
	if (s->map_copy[y + 1][x] == '1')
		jump = 0;
	if (s->map_copy[y][x - 1] == '1' || s->map_copy[y][x + 1] == '1')
		check_path_cbles(s, x, y - 1, jump);
	if (s->map_copy[y + 1][x - 1] == '1')
		check_path_cbles(s, x - 1, y, jump);
	if (s->map_copy[y + 1][x + 1] == '1')
		check_path_cbles(s, x + 1, y, jump);
	if (s->map_copy[y + 1][x] == '0' || s->map_copy[y + 1][x] == '.')
	{
		jump = 1;
		check_path_cbles(s, x, y + 1, jump);
		return ;
	}
	if (jump == 0)
	{
		check_path_cbles(s, x + 1, y, jump);
		check_path_cbles(s, x - 1, y, jump);
		check_path_cbles(s, x, y - 1, jump);
		check_path_cbles(s, x, y + 1, jump);
	}
}

void	check_path_exit(t_complete *s, int x, int y)
{
	if (x < 0 || y < 0 || x >= s->map_width || y >= s->map_height)
		return ;
	if (s->map_copy[y][x] == '1' || s->map_copy[y][x] == '-')
		return ;
	if (s->map_copy[y][x] == 'E')
	{
		s->map_copy[y][x] = '-';
		s->e_count2++;
		return ;
	}
	s->map_copy[y][x] = '-';
	find_path_exit(s, x, y, s->path_jump);

}

void	find_path_exit(t_complete *s, int x, int y, int jump)
{
	if (s->map_copy[y + 1][x] == '1')
		jump = 0;
	if (s->map_copy[y][x - 1] == '1' || s->map_copy[y][x + 1] == '1')
		check_path_exit(s, x, y - 1);
	if (s->map_copy[y + 1][x - 1] == '1')
		check_path_exit(s, x - 1, y);
	if (s->map_copy[y + 1][x + 1] == '1')
		check_path_exit(s, x + 1, y);
	if (s->map_copy[y + 1][x] == '0' || s->map_copy[y + 1][x] == '.')
	{
		jump = 1;
		check_path_exit(s, x, y + 1);
		return ;
	}
	if (jump == 0)
	{
		check_path_exit(s, x + 1, y);
		check_path_exit(s, x - 1, y);
		check_path_exit(s, x, y - 1);
		check_path_exit(s, x, y + 1);
	}
}

int	check_paths(t_complete *s)
{
	int i = -1;
	get_p_pos(s);
	while(s->map_copy[++i])
		printf("%s", s->map_copy[i]);
	printf("\n");
	i = -1;
	find_path_cbles(s, s->ppx, s->ppy, s->path_jump);
	if (s->c_count2 == s->c_count)
		write(1, "All collectables are reachable\n", 32);
	else
	{
		write(1, "Some collectables are not reachable\n", 36);
		return (check_leaks(s), 0);
	}
	while(s->map_copy[++i])
		printf("%s", s->map_copy[i]);
	printf("\n");
	i = -1;
	find_path_exit(s, s->ppx, s->ppy, s->path_jump);
	while(s->map_copy[++i])
		printf("%s", s->map_copy[i]);
	printf("\n");
	i = -1;
	printf("e_count: %d\n", s->e_count);
	printf("e_count2: %d\n", s->e_count2);
	if (s->e_count2 == s->e_count)
		write(1, "Exit is reachable\n", 19);
	else
	{
		write(1, "Exit is not reachable\n", 23);
		return (check_leaks(s), 0);
	}
	return (1);
}
