/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:59:28 by rhorvath          #+#    #+#             */
/*   Updated: 2024/07/05 13:04:09 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	clean_exit(t_data *data, bool error)
{
	int	i;

	i = -1;
	if (error)
		ft_putstr_fd("cub3d: Error\n", 2);
	while (++i < 15)
	{
		if (data->gun[i])
			mlx_delete_texture(data->gun[i]);
		if (i <= 4 && data->tex[i])
			mlx_delete_texture(data->tex[i]);
	}
	if (data->img)
		mlx_delete_image(data->mlx, data->img);
	if (data->minimap)
		mlx_delete_image(data->mlx, data->minimap);
	if (data->gun_img)
		mlx_delete_image(data->mlx, data->gun_img);
	if (data->mlx)
		mlx_terminate(data->mlx);
	exit(error);
}

void	init_player(t_data *data, t_player *player)
{
	int	temp;

	temp = data->map_x;
	data->map_x = data->map_y;
	data->map_y = temp;
	data->player = player;
	data->player->x = data->pos->y + 0.5;
	data->player->y = data->pos->x + 0.5;
	if (data->map[data->pos->x][data->pos->y] == 'S')
		data->player->dir = 180;
	else if (data->map[data->pos->x][data->pos->y] == 'E')
		data->player->dir = 90;
	else if (data->map[data->pos->x][data->pos->y] == 'W')
		data->player->dir = -90;
	else
		data->player->dir = 0;
}

void	get_bonus_tex(t_data *data)
{
	int	i;

	i = -1;
	data->gun[0] = mlx_load_png("./textures/gun/0.png");
	data->gun[1] = mlx_load_png("./textures/gun/1.png");
	data->gun[2] = mlx_load_png("./textures/gun/2.png");
	data->gun[3] = mlx_load_png("./textures/gun/3.png");
	data->gun[4] = mlx_load_png("./textures/gun/4.png");
	data->gun[5] = mlx_load_png("./textures/gun/5.png");
	data->gun[6] = mlx_load_png("./textures/gun/6.png");
	data->gun[7] = mlx_load_png("./textures/gun/7.png");
	data->gun[8] = mlx_load_png("./textures/gun/8.png");
	data->gun[9] = mlx_load_png("./textures/gun/9.png");
	data->gun[10] = mlx_load_png("./textures/gun/10.png");
	data->gun[11] = mlx_load_png("./textures/gun/11.png");
	data->gun[12] = mlx_load_png("./textures/gun/12.png");
	data->gun[13] = mlx_load_png("./textures/gun/13.png");
	data->gun[14] = mlx_load_png("./textures/gun/14.png");
	data->gun_img = NULL;
	data->tex[4] = mlx_load_png("textures/door.png");
	while (++i < 15)
		if (!data->gun[i])
			clean_exit(data, 1);
	if (!data->tex[4])
		clean_exit(data, 1);
}

// void	leaks()
// {
// 	system("leaks cub3D");
// }
// 	atexit(leaks);

int	main(int argc, char **argv)
{
	t_data		data;
	t_player	player;

	if (argc != 2)
		return (ft_error("Incorrect number of arguments!", 1, NULL));
	ft_parse(&data, argv);
	init_player(&data, &player);
	get_bonus_tex(&data);
	data.minimap = mlx_new_image(data.mlx, WIDTH / 5, HEIGHT / 5);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	mlx_image_to_window(data.mlx, data.minimap, WIDTH * 0.8, HEIGHT * 0.8);
	mlx_set_cursor_mode(data.mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(data.mlx, main_loop, &data);
	mlx_loop(data.mlx);
	clean_exit(&data, 0);
}
