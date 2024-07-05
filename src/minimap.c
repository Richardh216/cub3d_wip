/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoprea <aoprea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:54:41 by aoprea            #+#    #+#             */
/*   Updated: 2024/07/04 17:06:01 by aoprea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	minimap_put_tile(t_data *data, int x, int y, int color)
{
	unsigned int	i;
	unsigned int	size;

	i = 0;
	size = WIDTH / 100 + 1;
	while (i < size * size)
	{
		if (x + i % size >= 0 && x + i % size < data->minimap->width
			&& y + i / size >= 0 && y + i / size < data->minimap->height)
			mlx_put_pixel(data->minimap, x + i % size, y + i / size, color);
		i++;
	}
}

void	minimap_show_player(t_data *data)
{
	int	size;
	int	i;

	i = 0;
	size = WIDTH / 200;
	while (i < 15)
	{
		mlx_put_pixel(data->minimap, data->minimap->width / 2 + i
			* sin(rad(data->player->dir)), data->minimap->height / 2 - i
			* cos(rad(data->player->dir)) - size - 2, 0xFFFFFF88);
		i++;
	}
	i = 0;
	while (i < size * size)
	{
		mlx_put_pixel(data->minimap, data->minimap->width / 2 + i % size - 0.5
			* size + 1, data->minimap->height / 2 + i / size - size
			* 1.5 - 1, 0xFF000088);
		i++;
	}
}

void	render_minimap(t_data *data)
{
	unsigned int	i;
	unsigned int	j;
	t_pos			offset;

	i = -1;
	offset.x = (int)((data->player->x - (int)data->player->x) * WIDTH / 100);
	offset.y = (int)((data->player->y - (int)data->player->y) * WIDTH / 100);
	while (++i < data->minimap->width * data->minimap->height)
		mlx_put_pixel(data->minimap, i % data->minimap->width,
			i / data->minimap->width, 0x88888888);
	i = 0;
	while (i < 21)
	{
		j = 0;
		while (j < 21)
			if (is_solid(check_wall(data->player->x + j++ - 10, data->player->y
						+ i - 5, data)))
				minimap_put_tile(data, (j - 1) * WIDTH / 100 - offset.x,
					i * WIDTH / 100 - offset.y, 0xE97451CC);
		i++;
	}
	minimap_show_player(data);
}
