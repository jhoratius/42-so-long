/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draws.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:10:00 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/15 15:16:50 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_draws1(t_complete *s)
{
	int	i;

	i = 0;
	mlx_string_put(s->mlx, s->win, 10, 10, 0x00FF0000, "Hello, world!");
	ft_draw_sprite(s, s->exit_f[s->e_curr_f], s->ex, s->ey, false);
	while(i < s->collectible_count)
	{
		if(!s->collected[i])
			ft_draw_sprite(s, s->collect_f[s->c_curr_f], s->cx[i], s->cy[i], false);
		i++;
	}
	if(s->en_attack)
		ft_draw_sprite(s, s->atk_enemy_f[s->en_atk_curr_f], s->enx, s->eny, s->en_flip);
	else
		ft_draw_sprite(s, s->enemy_f[s->en_curr_f], s->enx, s->eny, s->en_flip);
	if(s->p_atk)
		ft_draw_sprite(s, s->atk_unit_f[s->atk_u_curr_f], s->px, s->py, s->p_flip);
	else
	{
		if(s->running)
			ft_draw_sprite(s, s->p_run_f[s->pr_curr_f], s->px, s->py, s->p_flip);
		else if(!(s->running))
			ft_draw_sprite(s, s->player_f[s->p_curr_f], s->px, s->py, s->p_flip);
	}
}

void	ft_draws2(t_complete *s)
{
	if(s->end_game)
		ft_draw_sprite(s, s->exit_banner, s->widthmap * 5 * SCALE, s->heightmap * 2 * SCALE, false);
	if(s->lose_game)
	{
		if(!s->keys[XK_Escape])
			ft_draw_sprite(s, s->lose_banner, s->widthmap * 5 * SCALE, s->heightmap * 2 * SCALE, false);
		else
			mlx_loop_end(s->mlx);
	}
	if(s->atk_launched && !s->end_attack)
		ft_draw_sprite(s, s->e_attack, s->ax[0], s->ay[0], s->atk_flip);
}