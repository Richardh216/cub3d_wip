/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:28:10 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/27 15:27:00 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_error(char *str, int flag, char *file)
{
	ft_putstr_fd("cub3d: Error", 2);
	if (str)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
	}
	ft_putchar_fd('\n', 2);
	if (file)
		free(file);
	if (flag)
		exit(flag);
	return (1);
}

void	path_error(t_data *data, char *str, char *file)
{
	int	i;

	if (data)
	{
		i = -1;
		while (++i < 4)
			if (data->tex[i])
				mlx_delete_texture(data->tex[i]);
		if (data->img)
			mlx_delete_image(data->mlx, data->img);
		if (data->mlx)
			mlx_terminate(data->mlx);
		if (data->map)
			;
	}
	if (str)
		ft_error(str, 1, file);
	if (file)
		free(file);
}

void	free_mat(char **mat)
{
	int	i;

	i = 0;
	if (!mat)
		return ;
	while (mat && mat[i])
	{
		if (mat[i])
			free(mat[i]);
		i++;
	}
	if (mat)
		free(mat);
}
