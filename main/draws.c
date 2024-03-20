/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draws.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:10:00 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/18 17:58:04 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_draws1(t_complete *s)
{
	int	i;

	i = 0;
	mlx_string_put(s->mlx, s->win, 10, 10, 0x00FF0000, "Hello, world!");
	ft_draw_sprite(s, s->exit, s->ex, s->ey, false);
	while(i < s->collectible_count)
	{
		if(!s->collected[i])
			ft_draw_sprite(s, s->collectable, s->cx[i], s->cy[i], false);
		i++;
	}
	if(s->end_game)
		ft_draw_sprite(s, s->exit_banner, s->widthmap * 5 * SCALE, s->heightmap * 2 * SCALE, false);
	ft_draw_sprite(s, s->player, s->px, s->py, s->p_flip);
}
