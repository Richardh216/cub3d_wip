/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:59:28 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/27 15:41:44 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_player(t_data *data, t_player *player)
{
	data->player = player;
	data->player->x = 5;
	data->player->y = 8;
	data->player->dir = 0.01;
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_player player;

	if (argc != 2)
		return (ft_error("Incorrect number of arguments!", 1, NULL));
	ft_parse(&data, argv);
	init_player(&data, &player);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	mlx_loop_hook(data.mlx, keyboard, &data);
	mlx_loop(data.mlx);
	mlx_delete_image(data.mlx, data.img);
	mlx_terminate(data.mlx);
	return (0);
}
