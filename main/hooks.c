/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:48:08 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/20 15:48:22 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	key_released_hook(int keycode, t_complete *param)
{
	param->keys[keycode] = false;
	return (0);
}

int	close_hook(t_complete *param)
{
	mlx_do_key_autorepeaton(param->mlx);
	// check_leaks(param);
	mlx_loop_end(param->mlx);
	return (0);
}

int	key_pressed_hook(int keycode, t_complete *param)
{
	printf("Key %c was pressed\n", keycode);
	if (keycode == XK_Escape)
	{
		mlx_do_key_autorepeaton(param->mlx);
		// check_leaks(param);
		mlx_loop_end(param->mlx);
	}
	else
		param->keys[keycode] = true;
	return (0);
}
