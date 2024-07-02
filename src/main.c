/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:59:28 by rhorvath          #+#    #+#             */
/*   Updated: 2024/07/02 16:56:31 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_player(t_data *data, t_player *player)
{
	data->player = player;
	// data->player->x = data->pos->x + 0.5;
	// data->player->y = data->pos->y + 0.5;
	// if (data->map[data->pos->y][data->pos->x] == 'S')
	// 	data->player->dir = 180;
	// else if (data->map[data->pos->y][data->pos->x] == 'E')
	// 	data->player->dir = 90;
	// else if (data->map[data->pos->y][data->pos->x] == 'W')
	// 	data->player->dir = -90;
	// else
	// 	data->player->dir = 0;
	data->player->x = 9.5;
	data->player->y = 1.5;
	data->player->dir = 90;
	//data->map[data->pos->y][data->pos->x] = '0';
}

void leaks()
{
	system("leaks cub3D");
}

//pos reading segf ?
//pass map x and y
//map get longest line, fill shorter ones up with spaces

int	main(int argc, char **argv)
{
	t_data		data;
	t_player	player;

	// atexit(leaks);
	if (argc != 2)
		return (ft_error("Incorrect number of arguments!", 1, NULL));
	ft_parse(&data, argv);
	printf("DATA POS: x: %d, y: %d\n", data.pos->x, data.pos->y);
	printf("MAP POS: %c\n", data.map[data.pos->x][data.pos->y]);
	printf("F_RGB %d\n", data.f_rgb);
	printf("C_RGB %d\n", data.c_rgb);
	printf("map_x: %d, map_y: %d\n", data.map_x, data.map_y);
	int	i = -1;
	while (data.map[++i])
		printf("%sEND\n", data.map[i]);
	init_player(&data, &player);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	mlx_set_cursor_mode(data.mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(data.mlx, keyboard, &data);
	mlx_loop(data.mlx);
	// mlx_delete_image(data.mlx, data.img);
	// mlx_terminate(data.mlx);
	path_error(&data, NULL, NULL);
	return (0);
}
