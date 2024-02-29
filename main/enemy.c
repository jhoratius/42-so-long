/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:29:12 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/02/29 15:53:05 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	get_enemy_pos(t_complete *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;

	while (s->map[i])
	{
		j = 0;
		while (s->map[i][j])
		{
			if(s->map[i][j] == 'E')
			{
				s->enx = j * 32 * SCALE;
				s->eny = i * 32 * SCALE;
				printf("enemy pos : %d, %d\n", s->enx, s->eny);
			}
			j++;
		}
		i++;
	}
	return ;
}
