/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:41:33 by aoprea            #+#    #+#             */
/*   Updated: 2024/06/27 15:37:42 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_collision(t_data *data, double speed)
{
	int map[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
	// if (data->player->x < 1)
	// 	data->player->x = 1;
	// if (data->player->x > MAP_X - 1)
	// 	data->player->x = MAP_X - 1;
	// if (data->player->y < 1)
	// 	data->player->y = 1;
	// if (data->player->y > MAP_Y - 1)
	// 	data->player->y = MAP_Y - 1;
	speed *= 1;
	double dir = data->player->dir - (180 * mlx_is_key_down(data->mlx, MLX_KEY_S) + 90 * mlx_is_key_down(data->mlx, MLX_KEY_D) - 90 * mlx_is_key_down(data->mlx, MLX_KEY_A)) / 1 + mlx_is_key_down(data->mlx, MLX_KEY_W);
	bool vertical = cos(dir) > sin (dir); 
	if (is_wall((int)data->player->x, (int)data->player->y, map))
	{
		if ((mlx_is_key_down(data->mlx, MLX_KEY_W)))
		{
			if (!is_wall((int)(data->player->x - sin(rad(data->player->dir)) * speed), (int)data->player->y, map))
				data->player->x -= sin(rad(data->player->dir)) * speed;
			else if (!is_wall((int)data->player->x, (int)(data->player->y + cos(rad(data->player->dir))) * speed, map))
				data->player->y += cos(rad(data->player->dir)) * speed;
			else
			{
				data->player->x -= sin(rad(data->player->dir)) * speed;
				data->player->y += cos(rad(data->player->dir)) * speed;
			}
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		{
			if (!is_wall((int)(data->player->x + sin(rad(data->player->dir)) * speed), (int)data->player->y, map))
				data->player->x += sin(rad(data->player->dir)) * speed;
			else if (!is_wall((int)data->player->x, (int)(data->player->y - cos(rad(data->player->dir))) * speed, map))
				data->player->y -= cos(rad(data->player->dir)) * speed;
			else
			{
				data->player->x += sin(rad(data->player->dir)) * speed;
				data->player->y -= cos(rad(data->player->dir)) * speed;
			}
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		{
			if (!is_wall((int)(data->player->x + cos(rad(data->player->dir)) * speed), (int)data->player->y, map))
				data->player->x += cos(rad(data->player->dir)) * speed;
			else if (!is_wall((int)data->player->x, (int)(data->player->y + sin(rad(data->player->dir))) * speed, map))
				data->player->y += sin(rad(data->player->dir)) * speed;
			else
			{
				data->player->x += cos(rad(data->player->dir)) * speed;
				data->player->y += sin(rad(data->player->dir)) * speed;
			}
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		{
			if (!is_wall((int)(data->player->x - cos(rad(data->player->dir)) * speed), (int)data->player->y, map))
				data->player->x -= cos(rad(data->player->dir)) * speed;
			else if (!is_wall((int)data->player->x, (int)(data->player->y - sin(rad(data->player->dir))) * speed, map))
				data->player->y -= sin(rad(data->player->dir)) * speed;
			else
			{
				data->player->x -= cos(rad(data->player->dir)) * speed;
				data->player->y -= sin(rad(data->player->dir)) * speed;
			}
			// if (!is_wall((int)(data->player->x + sin(rad(data->player->dir)) * speed), (int)data->player->y, map))
			// 	data->player->x += sin(rad(data->player->dir)) * speed;
			// else if (!is_wall((int)data->player->x, (int)(data->player->y - cos(rad(data->player->dir))) * speed, map))
			// 	data->player->y -= cos(rad(data->player->dir)) * speed;
			// else
			// {
			// 	data->player->x += sin(rad(data->player->dir)) * speed;
			// 	data->player->y -= cos(rad(data->player->dir)) * speed;
			// }
		}
	}
}

void	keyboard(void *param)
{
	t_data	*data;
	double	speed;

	data = (t_data *)param;
	speed = SPEED / (fabs(sin(rad(data->player->dir))) + fabs(cos(rad(data->player->dir))));
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
		data->player->x += sin(rad(data->player->dir)) * speed;
		data->player->y -= cos(rad(data->player->dir)) * speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		data->player->x -= sin(rad(data->player->dir)) * speed;
		data->player->y += cos(rad(data->player->dir)) * speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		data->player->x -= cos(rad(data->player->dir)) * speed;
		data->player->y -= sin(rad(data->player->dir)) * speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		data->player->x += cos(rad(data->player->dir)) * speed;
		data->player->y += sin(rad(data->player->dir)) * speed;
	}
	check_collision(data, speed);
	data->player->dir += ((data->player->dir <= -180.0) - (data->player->dir > 180.0)) * 360;
	render(data);
}