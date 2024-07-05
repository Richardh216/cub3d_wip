/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoprea <aoprea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:24:18 by aoprea            #+#    #+#             */
/*   Updated: 2024/07/02 15:46:02 by aoprea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	mouse_rotate(t_data *data)
{
	t_pos		pos;
	static int	mouse = -1;

	if (mouse == -1 && mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT))
		mouse = WIDTH / 2;
	if (mouse == -1)
		return ;
	mlx_get_mouse_pos(data->mlx, &pos.x, &pos.y);
	if (pos.x < 0)
	{
		pos.x += WIDTH;
		mouse += WIDTH;
		mlx_set_mouse_pos(data->mlx, pos.x, pos.y);
	}
	else if (pos.x > WIDTH)
	{
		pos.x -= WIDTH;
		mouse -= WIDTH;
		mlx_set_mouse_pos(data->mlx, pos.x, pos.y);
	}
	data->player->dir += ((double)FOV / WIDTH) * (pos.x - mouse);
	mouse = pos.x;
}

void	check_door_loop(t_data *data, t_vec vec, double *time)
{
	int	i;

	i = 0;
	while (i++ < 50)
	{
		if (check_wall((int)vec.x, (int)vec.y, data) == '1')
			break ;
		else if (check_wall((int)vec.x, (int)vec.y, data) == 'D')
		{
			data->map[(int)vec.y][(int)vec.x] = 'O';
			*time = 0;
			break ;
		}
		else if (check_wall((int)vec.x, (int)vec.y, data) == 'O')
		{
			data->map[(int)vec.y][(int)vec.x] = 'D';
			*time = 0;
			break ;
		}
		vec.x += sin(rad(data->player->dir)) * 0.1;
		vec.y -= cos(rad(data->player->dir)) * 0.1;
	}
}

void	check_door(t_data *data)
{
	int				i;
	t_vec			vec;
	static double	time = 0;

	time += data->mlx->delta_time;
	if (time < 0.3)
		return ;
	if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE))
	{
		i = 0;
		vec.x = data->player->x;
		vec.y = data->player->y;
		if (check_wall((int)vec.x, (int)vec.y, data) == 'O')
			return ;
		check_door_loop(data, vec, &time);
	}
}

void	move_back_forth(t_data *data, double speed)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		if (!is_solid(check_wall((int)(data->player->x + sin(rad(data->player-> \
					dir)) * speed * 1.1), (int)data->player->y, data)))
			data->player->x += sin(rad(data->player->dir)) * speed;
		if (!is_solid(check_wall((int)data->player->x, (int)(data->player->y
					- cos(rad(data->player->dir)) * speed * 1.1), data)))
			data->player->y -= cos(rad(data->player->dir)) * speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		if (!is_solid(check_wall((int)(data->player->x - sin(rad(data->player-> \
					dir)) * speed * 1.1), (int)data->player->y, data)))
			data->player->x -= sin(rad(data->player->dir)) * speed;
		if (!is_solid(check_wall((int)data->player->x, (int)(data->player->y
					+ cos(rad(data->player->dir)) * speed * 1.1), data)))
			data->player->y += cos(rad(data->player->dir)) * speed;
	}
}

void	move_left_right(t_data *data, double speed)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		if (!is_solid(check_wall((int)(data->player->x - cos(rad(data->player-> \
					dir)) * speed * 1.1), (int)data->player->y, data)))
			data->player->x -= cos(rad(data->player->dir)) * speed;
		if (!is_solid(check_wall((int)data->player->x, (int)(data->player->y
					- sin(rad(data->player->dir)) * speed * 1.1), data)))
			data->player->y -= sin(rad(data->player->dir)) * speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		if (!is_solid(check_wall((int)(data->player->x + cos(rad(data-> \
			player->dir)) * speed * 1.1), (int)data->player->y, data)))
			data->player->x += cos(rad(data->player->dir)) * speed;
		if (!is_solid(check_wall((int)data->player->x, (int)(data->player->y
					+ sin(rad(data->player->dir)) * speed * 1.1), data)))
			data->player->y += sin(rad(data->player->dir)) * speed;
	}
}
