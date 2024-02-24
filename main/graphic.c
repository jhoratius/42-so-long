/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:26:47 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/02/24 17:17:04 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/so_long.h"

unsigned int get_pixel(t_img *img, int x, int y, bool flipped)
{
	if (flipped)
		return (((int *)img->data)[(int)(y / SCALE) * img->width + img->width - (int)(x / SCALE) - 1]);
	return (((int *)img->data)[(int)(y / SCALE) * img->width + (int)(x / SCALE)]);
}
void	clear_screen(t_img *img, unsigned int color)
{
	int i;
	int j;

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
	ptr = mlx_xpm_file_to_image(param->mlx, imagePath, &param->widthmap, &param->heightmap);
	if(!ptr){
		printf("Error: Unable to load %s\n", imagePath);
		return (NULL);
	}
	return (ptr);
}