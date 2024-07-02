/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoprea <aoprea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:04:54 by aoprea            #+#    #+#             */
/*   Updated: 2024/07/01 18:38:50 by aoprea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_wall(t_data *data, int start, int end, t_ray ray)
{
	uint32_t	*pixels;
	t_pos		tex;
	int			i;
	int			color;

	i = 0;
	if (ray.c_dir < 2)
		tex.x = (int)(ray.h.x * data->tex[ray.c_dir]->width)
			% data->tex[ray.c_dir]->width;
	else
		tex.x = (int)(ray.v.y * data->tex[ray.c_dir]->width)
			% data->tex[ray.c_dir]->width;
	pixels = (uint32_t *)data->tex[ray.c_dir]->pixels;
	while (start + i < end)
	{
		if (start + i >= 0 && start + i < HEIGHT)
		{
			tex.y = i * 1.0 * data->tex[ray.c_dir]->height / (end - start);
			color = pixels[tex.y * data->tex[ray.c_dir]->width + tex.x];
			mlx_put_pixel(data->img, ray.x, start + i,
				(u_int32_t)reverse_bytes(color));
		}
		i++;
	}
}

double	check_ray(t_ray *ray, t_player *p, int i, char **map)
{
	if (i > 50)
		return (ray->dist);
	if (sqrt(pow(p->x - ray->h.x, 2) + pow(p->y - ray->h.y, 2))
		< sqrt(pow(p->x - ray->v.x, 2) + pow(p->y - ray->v.y, 2)))
	{
		ray->type = check_wall(ray->h.x, ray->h.y - (fabs(ray->dir) < 90), map);
		ray->c_dir = fabs(ray->dir) > 90;
		if (ray->type == '1' || ray->type == 'D')
			return (sqrt(pow(p->x - ray->h.x, 2) + pow(p->y - ray->h.y, 2)));
		ray->h.x += tan(rad(ray->dir)) * (1 - (fabs(ray->dir) > 90) % 2 * 2);
		ray->h.y += 1 - 2 * (fabs(ray->dir) < 90);
	}
	else
	{
		ray->type = check_wall(ray->v.x - (ray->dir < 0), ray->v.y, map);
		ray->c_dir = 2 + (ray->dir < 0);
		if (ray->type == '1' || ray->type == 'D')
			return (sqrt(pow(p->x - ray->v.x, 2) + pow(p->y - ray->v.y, 2)));
		ray->v.x += 1 - 2 * (ray->dir < 0);
		ray->v.y += -(tan(rad(90 - fabs(ray->dir))));
	}
	return (0);
}

void	render_column(int x, t_data *data, t_player p)
{
	t_ray	ray;
	double	wall;
	int		i;

	ray.dist = 100000;
	ray.x = x;
	i = 0;
	ray.dir = p.dir - (FOV / 2) + ((double)FOV / WIDTH) * x;
	ray.dir += ((ray.dir <= -180.0) - (ray.dir > 180.0)) * 360;
	ray.h.y = (int)p.y + (fabs(ray.dir) > 90);
	ray.h.x = p.x + (p.y - ray.h.y) * tan(rad(ray.dir));
	ray.v.x = (int)p.x + (ray.dir > 0);
	ray.v.y = p.y - (p.x - ray.v.x) * -tan(rad(90 - ray.dir));
	while (i++ < 50)
		ray.dist = check_ray(&ray, &p, i, data->map);
	ray.dist *= cos(rad(ray.dir - p.dir));
	wall = 1 / ray.dist * (double)(WIDTH / 2) / tan(rad(FOV / 2));
	draw_line(data, ray.x, 0, (HEIGHT - wall) / 2);
	draw_wall(data, (HEIGHT - wall) / 2, (HEIGHT + wall) / 2, ray);
	draw_line(data, ray.x, (HEIGHT + wall) / 2 - 1, HEIGHT);
}

// void	render_minimap(t_data *data)
// {
// }

void	render(t_data *data)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
		render_column(x, data, *data->player);
}
