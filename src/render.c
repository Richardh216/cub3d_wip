/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoprea <aoprea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:04:54 by aoprea            #+#    #+#             */
/*   Updated: 2024/06/27 12:53:03 by aoprea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double rad(double degrees) 
{
	return (degrees * (M_PI / 180.0));
}

double	scale(double x, double min, double max, double old_max)
{
	return ((max - min) * x / old_max + min);
}

void	draw_line(mlx_image_t *image, int x, int start, int end, int color)
{
	if (start < 0)
		start = 0;
	if (end > HEIGHT)
		end = HEIGHT;
	while (start < end)
		mlx_put_pixel(image, x, start++, color);
}

void	draw_wall(t_data *data, int x, int start, int end)
{
	//mlx_image_t *img = mlx_texture_to_image(data->mlx, data->tex[0]);
	//int color = img;
	//printf("%d\n", color);
	//(void)img;
	if (start < 0)
		start = 0;
	if (end > HEIGHT)
		end = HEIGHT;
	while (start < end)
		mlx_put_pixel(data->img, x, start++, 0x8B4F39FF);
}

int	is_wall(int x, int y, int map[MAP_Y][MAP_X])
{
	if (x > MAP_X - 1 ||  y > MAP_Y - 1 || x < 0 || y < 0)
		return (0);
	return (map[y][x]);
}

void	render_column(int x, t_data *data, t_player p)
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
	(void)data;
	t_ray	h;
	t_ray	v;
	double	ray_dir;
	double	dist = 100000;
	int i = 0;

	ray_dir = p.dir - (FOV / 2) + ((double)FOV / WIDTH) * x;
	ray_dir += ((ray_dir <= -180.0) - (ray_dir > 180.0)) * 360;
	h.y = (int)p.y + (fabs(ray_dir) > 90);
	h.x = p.x + (p.y - h.y) * tan(rad(ray_dir));
	v.x = (int)p.x + (ray_dir > 0);
	v.y = p.y - (p.x - v.x) * -tan(rad(90 - ray_dir));
	while (i++ < 50)
	{
		if (sqrt(pow(p.x - h.x, 2) + pow(p.y - h.y, 2)) < sqrt(pow(p.x - v.x, 2) + pow(p.y - v.y, 2)))
		{
			if (h.x >= 1 && h.x <= MAP_X - 1 && is_wall((int)h.x, (int)h.y - (fabs(ray_dir) < 90), map))
			{
				dist = sqrt(pow(p.x - h.x, 2) + pow(p.y - h.y, 2));
				break ;
			}
			h.x += tan(rad(ray_dir)) * (1 - (fabs(ray_dir) > 90) % 2 * 2);
			h.y += 1 - 2 * (fabs(ray_dir) < 90);
		}
		else
		{
			if (v.y >= 1 && v.y <= MAP_Y - 1 && is_wall((int)v.x - (ray_dir < 0), (int)v.y, map))
			{
				dist = sqrt(pow(p.x - v.x, 2) + pow(p.y - v.y, 2));
				break ;
			}
			v.x += 1 - 2 * (ray_dir < 0);
			v.y += -(tan(rad(90 - fabs(ray_dir))));
		}
	}
	dist *= cos(rad(ray_dir - p.dir));
	double wall = 1 / dist * (double)(WIDTH / 2) / (double)tan(rad(FOV / 2));
	draw_line(data->img, x, 0, (HEIGHT - wall) / 2, 0x47adccff);
	draw_wall(data, x, (HEIGHT - wall) / 2, HEIGHT / 2 + wall / 2);
	draw_line(data->img, x, (HEIGHT + wall) / 2 - 1, HEIGHT, 0x439e3cff);
}

void	render(t_data *data)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
		render_column(x, data, *data->player);
}
