/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:59:28 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/28 17:41:04 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_player(t_data *data, t_player *player)
{
	data->player = player;
	data->player->x = 1.5;
	data->player->y = 1.5;
	data->player->dir = 90;
}

void leaks()
{
	system("leaks cub3D");
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_player player;

	// atexit(leaks);
	if (argc != 2)
		return (ft_error("Incorrect number of arguments!", 1, NULL));
	ft_parse(&data, argv);
	init_player(&data, &player);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	mlx_loop_hook(data.mlx, keyboard, &data);
	mlx_loop(data.mlx);
	mlx_delete_image(data.mlx, data.img);
	mlx_terminate(data.mlx);
	// path_error(&data, NULL, NULL);
	return (0);
}
