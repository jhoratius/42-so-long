/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_steps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:50:54 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/04/02 14:45:58 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	print_steps(t_complete *s, char *moves)
{
	calculate_steps(s);
	mlx_string_put(s->mlx, s->win, 10 * SCALE,
		20 * SCALE, 0xFFFFFF, "Nb de pas : ");
	mlx_string_put(s->mlx, s->win, 40 * SCALE,
		20 * SCALE, 0xFFFFFF, moves);
}

void	calculate_steps(t_complete *s)
{
	int		dist;

	dist = sqrt((s->px - s->appx) * (s->px - s->appx))
		+ ((s->py - s->appy) * (s->py - s->appy));
	if (dist > 100)
	{
		s->appx = s->px;
		s->appy = s->py;
		s->nb_pas++;
		dist = 0;
	}
}
