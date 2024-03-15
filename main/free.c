/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:21:31 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/15 14:07:57 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/so_long.h"

void	check_free(t_complete *s)
{
	free_pointers(s->mlx);
	free_pointers(s->win);
	free_pointers(s->floor);
	free_pointers(s->barrier);
	free_pointers(s->player);
	free_pointers(s->enemy);
	free_pointers(s->e_attack);
	free_pointers(s->exit);
	free_pointers(s->collectable);
	free_pointers(s->collectible_count);
	free_pointers(s->exit_banner);
	free_pointers(s->lose_banner);
}

void	free_pointers(void *ptr)
{
	if(!ptr)
		return ;
	ptr = NULL;
	free(ptr);
}

void	check_sprites(t_complete *s)
{
	destroy_sprites(s, s->player_f, 4);
	destroy_sprites(s, s->p_run_f, 5);
	destroy_sprites(s, s->collect_f, 4);
	destroy_sprites(s, s->exit_f, 4);
	destroy_sprites(s, s->enemy_f, 3);
	destroy_sprites(s, s->atk_enemy_f, 3);
	destroy_sprites(s, s->atk_unit_f, 4);
}

void	destroy_sprites(t_complete *s, t_img *img, int n)
{
	int		i;

	i = 0;
	if(!img)
		return ;
	else
	{
		while(i < n - 1)
		{
			if(img[i].image && img[i].image != NULL)
				mlx_destroy_image(s->mlx, img[i].image);
			i++;
		}
	}
}

void	check_leaks(t_complete *s)
{
	check_free(s);
	// check_sprites(s);
}
