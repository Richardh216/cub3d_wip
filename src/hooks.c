/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:41:33 by aoprea            #+#    #+#             */
/*   Updated: 2024/06/27 18:45:49 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	keyboard(void *param)
{
	t_data	*data;
	double	speed;
	int 	keys_pressed;
	int map[20][20] = {
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

	data = (t_data *)param;
	keys_pressed = (mlx_is_key_down(data->mlx, MLX_KEY_W) + mlx_is_key_down(data->mlx, MLX_KEY_A)
				 + mlx_is_key_down(data->mlx, MLX_KEY_S) + mlx_is_key_down(data->mlx, MLX_KEY_D));
	keys_pressed = (int)pow((double)keys_pressed, keys_pressed == 2);
	speed = SPEED / (fabs(sin(rad(data->player->dir))) + fabs(cos(rad(data->player->dir)))) / keys_pressed;
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
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		if (!is_wall((int)(data->player->x + sin(rad(data->player->dir)) * speed), (int)data->player->y, map))
			data->player->x += sin(rad(data->player->dir)) * speed;
		if (!is_wall((int)data->player->x, (int)(data->player->y - cos(rad(data->player->dir)) * speed), map))
			data->player->y -= cos(rad(data->player->dir)) * speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		if (!is_wall((int)(data->player->x - sin(rad(data->player->dir)) * speed), (int)data->player->y, map))
			data->player->x -= sin(rad(data->player->dir)) * speed;
		if (!is_wall((int)data->player->x, (int)(data->player->y + cos(rad(data->player->dir)) * speed), map))
			data->player->y += cos(rad(data->player->dir)) * speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		if (!is_wall((int)(data->player->x - cos(rad(data->player->dir)) * speed), (int)data->player->y, map))
			data->player->x -= cos(rad(data->player->dir)) * speed;
		if (!is_wall((int)data->player->x, (int)(data->player->y - sin(rad(data->player->dir)) * speed), map))
			data->player->y -= sin(rad(data->player->dir)) * speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		if (!is_wall((int)(data->player->x + cos(rad(data->player->dir)) * speed), (int)data->player->y, map))
			data->player->x += cos(rad(data->player->dir)) * speed;
		if (!is_wall((int)data->player->x, (int)(data->player->y + sin(rad(data->player->dir)) * speed), map))
			data->player->y += sin(rad(data->player->dir)) * speed;
	}
	data->player->dir += ((data->player->dir <= -180.0) - (data->player->dir > 180.0)) * 360;
	render(data);
}