/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draws.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:10:00 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/26 16:07:02 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_draws1(t_complete *s)
{
	int	i;

	i = 0;
	ft_draw_sprite(s, s->exit, s->ex, s->ey);
	while (i < s->collectible_count)
	{
		if (!s->collected[i])
			ft_draw_sprite(s, s->collectable, s->cx[i], s->cy[i]);
		i++;
	}
	if (s->end_game)
		mlx_loop_end(s->mlx);
	ft_draw_sprite(s, s->player, s->px, s->py);
}
