/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:21:31 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/02/29 11:26:39 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/so_long.h"

void	free_init(t_complete *s)
{
	free(s->mlx);
	free(s->win);
	free(s->img);
}

void	free_affectation(t_complete *s)
{
	free(s->collectable);
	free(s->floor);
	free(s->barrier);
	free(s->player);
	free(s->exit);
	free(s->floor);
	free(s->barrier);
	free(s->p_current_frame);
	free(s->p_last_frame_time);
	free(s->pr_current_frame);
	free(s->pr_last_frame_time);
	free(s->c_current_frame);
	free(s->c_last_frame_time);
	free(s->map);
}

void	destroy_sprites(t_complete *s)
{
	mlx_destroy_image(s->mlx, s->collectable);
	mlx_destroy_image(s->mlx, s->floor);
	mlx_destroy_image(s->mlx, s->barrier);
	mlx_destroy_image(s->mlx, s->player);
	mlx_destroy_image(s->mlx, s->exit);
	mlx_destroy_image(s->mlx, s->map);
	
}