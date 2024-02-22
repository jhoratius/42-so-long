/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:25:35 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/02/22 17:12:50 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// t_complete *param;

void	character_animated(t_complete *param)
{
	char	file_path[64];
	int		i;

	i = 0;
	while (i < 4)
	{
		ft_sprintf(file_path, "sprites/character/passive/pass%d.xpm", i);
		param->player_frames[i] = load_xpm_image(param, file_path);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		ft_sprintf(file_path, "sprites/character/run/run%d.xpm", i);
		param->p_run_frames[i] = load_xpm_image(param, file_path);
		i++;
	}
}

void	collectible_animated(t_complete *param)
{
	char	file_path[64];
	int		i;

	i = 0;
	while (i < 4)
	{
		ft_sprintf(file_path, "sprites/collectible/cube%d.xpm", i);
		param->collect_frames[i] = load_xpm_image(param, file_path);
		i++;
	}
}