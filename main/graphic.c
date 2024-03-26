/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:26:47 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/26 16:09:55 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

unsigned int	get_pixel(t_img *img, int x, int y, bool flipped)
{
	if (flipped)
		return (((int *)img->data)[(int)(y / SCALE) *img->width
			+ img->width - (int)(x / SCALE) - 1]);
	return (((int *)img->data)[(int)(y / SCALE)
		*img->width + (int)(x / SCALE)]);
}

void	clear_screen(t_img *img, unsigned int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < img->width)
	{
		j = 0;
		while (j < img->height)
		{
			((int *)img->data)[j * img->width + i] = color;
			j++;
		}
		i++;
	}
}

void	*load_xpm_image(t_complete *param, char *imagePath)
{
	void	*ptr;

	printf("Loading %s\n", imagePath);
	ptr = mlx_xpm_file_to_image(param->mlx, imagePath,
			&param->widthmap, &param->heightmap);
	if (!ptr)
	{
		printf("Error: Unable to load %s\n", imagePath);
		return (NULL);
	}
	return (ptr);
}

void	ft_draw_sprite(t_complete *game, t_img *img, int x, int y)
{
	int				i;
	int				j;
	unsigned int	color;

	i = -1;
	while (++i < img->width * SCALE)
	{
		j = -1;
		while (++j < img->height * SCALE)
		{
			if (j + y < 0 || j + y >= game->img->height
				|| i + x < 0 || i + x >= game->img->width)
				continue ;
			if (img == game->player)
				color = get_pixel(img, i, j, game->p_flip);
			else
				color = get_pixel(img, i, j, false);
			if (color == 0xFF000000)
				continue ;
			((int *)game->img->data)[(y + j)
				* game->img->width + (x + i)] = color;
		}
	}
}

bool	collide(t_hitbox rect1, t_hitbox rect2)
{
	return (rect1.x < rect2.x + rect2.width
		&& rect1.x + rect1.width > rect2.x
		&& rect1.y < rect2.y + rect2.height
		&& rect1.height + rect1.y > rect2.y);
}
