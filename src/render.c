/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:04:54 by aoprea            #+#    #+#             */
/*   Updated: 2024/07/05 12:13:16 by rhorvath         ###   ########.fr       */
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
	tex.x = (int)(((ray.c_dir < 2) * ray.h.x + (ray.c_dir >= 2) * ray.v.y)
			* data->tex[((ray.type != 'D') * ray.c_dir)
			+ ((ray.type == 'D') * 4)]
			->width) % data->tex[((ray.type != 'D') * ray.c_dir)
		+ ((ray.type == 'D') * 4)]->width;
	if (ray.type == 'D')
		ray.c_dir = 4;
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

double	check_ray(t_ray *ray, t_player *p, int i, t_data *data)
{
	if (i > 50)
		return (ray->dist);
	if (sqrt(pow(p->x - ray->h.x, 2) + pow(p->y - ray->h.y, 2))
		< sqrt(pow(p->x - ray->v.x, 2) + pow(p->y - ray->v.y, 2)))
	{
		ray->type = check_wall(ray->h.x, ray->h.y
				- (fabs(ray->dir) < 90), data);
		ray->c_dir = fabs(ray->dir) > 90;
		if (ray->type == '1' || ray->type == 'D')
			return (sqrt(pow(p->x - ray->h.x, 2) + pow(p->y - ray->h.y, 2)));
		ray->h.x += tan(rad(ray->dir)) * (1 - (fabs(ray->dir) > 90) % 2 * 2);
		ray->h.y += 1 - 2 * (fabs(ray->dir) < 90);
	}
	else
	{
		ray->type = check_wall(ray->v.x - (ray->dir < 0), ray->v.y, data);
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
		ray.dist = check_ray(&ray, &p, i, data);
	ray.dist *= cos(rad(ray.dir - p.dir));
	wall = 1 / ray.dist * (double)(WIDTH / 2) / tan(rad(FOV / 2));
	draw_line(data, ray.x, 0, (HEIGHT - wall) / 2);
	draw_wall(data, (HEIGHT - wall) / 2, (HEIGHT + wall) / 2, ray);
	draw_line(data, ray.x, (HEIGHT + wall) / 2 - 1, HEIGHT);
}

void	shoot(t_data *data, int *frame)
{
	static double	time = 0;

	time += data->mlx->delta_time;
	if ((*frame == 0 && mlx_is_mouse_down(data->mlx,
				MLX_MOUSE_BUTTON_LEFT)) || (*frame != 0 && time > 0.05))
		*frame += 1;
	if (time > 0.05)
		time = 0;
	if (*frame == 15)
		*frame = 0;
}

void	render(t_data *data)
{
	int			x;
	static int	frame = 0;

	if (data->gun_img)
		mlx_delete_image(data->mlx, data->gun_img);
	shoot(data, &frame);
	data->gun_img = mlx_texture_to_image(data->mlx, data->gun[frame]);
	mlx_resize_image(data->gun_img, (int)((double)data->gun_img->width
			* (double)WIDTH / 750),
		(int)((double)data->gun_img->height * (double)WIDTH / 750));
	mlx_image_to_window(data->mlx, data->gun_img, WIDTH / 2 - 100
		* WIDTH / 1500, HEIGHT - 97 * WIDTH / 750);
	x = -1;
	while (++x < WIDTH)
		render_column(x, data, *data->player);
	render_minimap(data);
}
