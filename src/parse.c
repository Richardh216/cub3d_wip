/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:12:39 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/18 14:35:28 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_data(t_data *data)
{
	int	i;

	i = -1;
	data->mlx = NULL;
	data->img = NULL;
	data->map = NULL;
	while (++i < 4)
		data->tex[i] = NULL;
}

void	ft_parse(t_data *data, char **argv)
{
	int		i;

	(void)data;
	i = ft_strlen(argv[1]);
	if (i < 4)
		ft_error("Incorrect file name!", 1);
	if (ft_strncmp(&argv[1][i - 4], ".cub", 4))
		ft_error("Incorrect file format!", 1);
	init_data(data);
}
