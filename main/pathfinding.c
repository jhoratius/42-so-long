/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:07:00 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/30 18:18:52 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/so_long.h"

void	check_path_cbles(t_complete *s, int x, int y, int jump)
{
	if (x < 0 || y < 0 || x >= s->map_width || y >= s->map_height)
		return ;
	if (s->map_copy[y][x] == '1' || s->map_copy[y][x] == '.')
		return ;
	if (s->map_copy[y][x] == 'C')
	{
		s->c_count2++;
	}
	if (s->map_copy[y][x] == 'E' || s->map_copy[y][x] == 'P')
	{
		find_path_cbles(s, x, y, jump);
		return ;
	}
	s->map_copy[y][x] = '.';
	find_path_cbles(s, x, y, jump);
	return ;
}

void	find_path_cbles(t_complete *s, int x, int y, int jump)
{
	if(s->map_copy[y + 1][x] == '1')
		jump = 0;
	if(s->map_copy[y][x - 1] == '1' || s->map_copy[y][x + 1] == '1')
		check_path_cbles(s, x, y - 1, jump);
	if(s->map_copy[y + 1][x - 1] == '1')
		check_path_cbles(s, x - 1, y, jump);
	if (s->map_copy[y + 1][x + 1] == '1')
		check_path_cbles(s, x + 1, y, jump);
	if (s->map_copy[y + 1][x] == '0'|| s->map_copy[y + 1][x] == '.')
	{
		jump = 1;
		check_path_cbles(s, x, y + 1, jump);
		return ;
	}
	if(jump == 0)
	{
		check_path_cbles(s, x + 1, y, jump);
		check_path_cbles(s, x - 1, y, jump);
		check_path_cbles(s, x, y - 1, jump);
		check_path_cbles(s, x, y + 1, jump);
	}
	// check_path_cbles(s, x + 1, y);
	// check_path_cbles(s, x - 1, y);
	// check_path_cbles(s, x, y - 1);
	// check_path_cbles(s, x, y + 1);
}

void	check_path_exit(t_complete *s, int x, int y, int jump)
{
	if(x < 0 || y < 0 || x >= s->map_width || y >= s->map_height)
		return ;
	if(s->map_copy[y][x] == '1' || s->map_copy[y][x] == '-')
		return ;
	if(s->map_copy[y][x] == 'E')
	{
		if((s->map_copy[y + 1][x] == '1') && (s->map_copy[y - 1][x] == '1')
		&& (s->map_copy[y][x + 1] == '1') && (s->map_copy[y][x - 1] == '1'))
		{
			s->map_copy[y][x] = '-';
			return ;
		}
		s->e_count2++;
	}
	s->map_copy[y][x] = '-';
	find_path_exit(s, x, y, s->path_jump);
	return ;
}

void	find_path_exit(t_complete *s, int x, int y, int jump)
{
	if(s->map_copy[y + 1][x] == '1')
		jump = 0;
	if(s->map_copy[y][x - 1] == '1' || s->map_copy[y][x + 1] == '1')
		check_path_cbles(s, x, y - 1, jump);
	if(s->map_copy[y + 1][x - 1] == '1')
		check_path_cbles(s, x - 1, y, jump);
	if (s->map_copy[y + 1][x + 1] == '1')
		check_path_cbles(s, x + 1, y, jump);
	if (s->map_copy[y + 1][x] == '0'|| s->map_copy[y + 1][x] == '.')
	{
		jump = 1;
		check_path_cbles(s, x, y + 1, jump);
		return ;
	}
	if(jump == 0)
	{
		check_path_cbles(s, x + 1, y, jump);
		check_path_cbles(s, x - 1, y, jump);
		check_path_cbles(s, x, y - 1, jump);
		check_path_cbles(s, x, y + 1, jump);
	}
}

int	check_paths(t_complete *s)
{
	int i = -1;
	get_p_pos(s);
	while(s->map_copy[++i])
		printf("%s", s->map_copy[i]);
	printf("\n");
	printf("ppx: %d, ppy: %d\n", s->ppx, s->ppy);
	find_path_cbles(s, s->ppx, s->ppy, s->path_jump);
	printf("c_count : %d\n", s->c_count);
	printf("c_count2: %d\n", s->c_count2);
	if (s->c_count2 == s->c_count)
		write(1, "All collectables are reachable\n", 32);
	else
	{
		write(1, "Some collectables are not reachable\n", 36);
		// return (check_leaks(s), 0);
	}
	i = -1;
	while(s->map_copy[++i])
		printf("%s", s->map_copy[i]);
	printf("\n");
	printf("ok ok\n");
	// if (!(find_path_jump_c(s, s->map_copy)))
		// return (check_leaks(s), 0);
	// i = -1;
	// while(s->map_copy[++i])
	// 	printf("%s", s->map_copy[i]);
	// printf("\n");
	i = -1;
	find_path_exit(s, s->ppx, s->ppy, s->path_jump);
	printf("e_count : %d\n", s->e_count);
	printf("e_count2: %d\n", s->e_count2);
	while(s->map_copy[++i])
		printf("%s", s->map_copy[i]);
	printf("\n");
	if (s->e_count2 == s->e_count)
		write(1, "Exit is reachable\n", 19);
	else
	{
		write(1, "Exit is not reachable\n", 23);
		// return (check_leaks(s), 0);
	}
	return (1);
}
