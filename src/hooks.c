/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoprea <aoprea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:41:33 by aoprea            #+#    #+#             */
/*   Updated: 2024/07/04 16:57:48 by aoprea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	calc_speed(t_data *data)
{
	int		keys_pressed;

	keys_pressed = (mlx_is_key_down(data->mlx, MLX_KEY_W) + mlx_is_key_down(
				data->mlx, MLX_KEY_A) + mlx_is_key_down(
				data->mlx, MLX_KEY_S) + mlx_is_key_down(data->mlx, MLX_KEY_D));
	keys_pressed = (int)pow((double)keys_pressed, keys_pressed == 2);
	return (SPEED / keys_pressed * data->mlx->delta_time
		* (1 + mlx_is_key_down(data->mlx, MLX_KEY_LEFT_SHIFT)));
}

void	main_loop(void *param)
{
	t_data	*data;
	double	speed;

	data = (t_data *)param;
	speed = calc_speed(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_delete_image(data->mlx, data->img);
		mlx_terminate(data->mlx);
		exit(0);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player->dir -= 2.5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player->dir += 2.5;
	move_back_forth(data, speed);
	move_left_right(data, speed);
	mouse_rotate(data);
	data->player->dir += ((data->player->dir <= -180.0)
			- (data->player->dir > 180.0)) * 360;
	check_door(data);
	render(data);
}
