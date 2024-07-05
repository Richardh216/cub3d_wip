/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoprea <aoprea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:27:36 by aoprea            #+#    #+#             */
/*   Updated: 2024/07/02 19:27:12 by aoprea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_solid(char wall)
{
	return (wall == '1' || wall == 'D');
}

double	rad(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

int	reverse_bytes(uint32_t pixel)
{
	return (((pixel & 0x000000FF) << 24)
		| ((pixel & 0x0000FF00) << 8)
		| ((pixel & 0x00FF0000) >> 8)
		| ((pixel & 0xFF000000) >> 24));
}

void	draw_line(t_data *data, int x, int start, int end)
{
	int	color;

	if (start < 0)
		start = 0;
	if (end > HEIGHT)
		end = HEIGHT;
	if (start == 0)
		color = data->top[0] << 24 | data->top[1] << 16
			| data->top[2] << 8 | 255;
	else
		color = data->bottom[0] << 24 | data->bottom[1] << 16
			| data->bottom[2] << 8 | 255;
	while (start < end)
		mlx_put_pixel(data->img, x, start++, color);
}

int	check_wall(int x, int y, t_data *data)
{
	if (x >= data->map_x || y >= data->map_y || x < 0 || y < 0)
		return (0);
	return (data->map[y][x]);
}
