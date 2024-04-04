/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:21:31 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/04/03 19:35:01 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	check_sprites(t_complete *s)
{
	destroy_sprite(s, s->player);
	destroy_sprite(s, s->collectable);
	destroy_sprite(s, s->exit);
	destroy_sprite(s, s->floor);
	destroy_sprite(s, s->barrier);
	destroy_sprite(s, s->enemy);
	destroy_sprite(s, s->exit_banner);
	destroy_sprite(s, s->img);
}

void	destroy_sprite(t_complete *s, t_img *img)
{
	if (img != NULL)
		mlx_destroy_image(s->mlx, img);
	else
		return ;
}

void	free_map(t_complete *s)
{
	int	i;

	i = 0;
	while (s->map[i])
	{
		free(s->map[i]);
		i++;
	}
	free(s->map);
}

void	free_copy_map(t_complete *s)
{
	int	i;

	i = 0;
	while (s->map_copy[i])
	{
		free(s->map_copy[i]);
		i++;
	}
	free(s->map_copy);
}

void	check_leaks(t_complete *s)
{
	check_sprites(s);
	free(s->cx);
	free(s->cy);
	free(s->collected);
	if (s->map)
		free_map(s);
	if (s->map_copy)
		free_copy_map(s);
	if (s->mlx)
	{
		mlx_destroy_window(s->mlx, s->win);
		mlx_destroy_display(s->mlx);
		free(s->mlx);
	}
}
