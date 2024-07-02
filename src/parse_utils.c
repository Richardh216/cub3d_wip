/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:06:31 by rhorvath          #+#    #+#             */
/*   Updated: 2024/07/02 14:13:12 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	skip_leading_spaces(char *str, int pos)
{
	while (str[pos])
	{
		if (str[pos] == ' ' || str[pos] == '\t')
			pos++;
		else
			return (pos);
	}
	return (pos);
}

void	ft_val_check(t_data *data)
{
	int	i;

	i = -1;
	while (data->bottom[++i] && i < 3)
		if (data->bottom[i] < 0 || data->bottom[i] > 255)
			ft_error("Incorrect RGB values!", 1, NULL);
	i = -1;
	while (data->top[++i] && i < 3)
		if (data->top[i] < 0 || data->top[i] > 255)
			ft_error("Incorrect RGB values!", 1, NULL);
	data->c_rgb = (data->top[0] << 16) | (data->top[1] << 8) | data->top[2];
	data->f_rgb = (data->bottom[0] << 16)
		| (data->bottom[1] << 8) | data->bottom[2];
}

void	check_help(char *str, int i)
{
	if (!ft_isdigit(str[i]) && str[i] != ' '
		&& str[i] != '\t' && str[i] != ',')
		ft_error("No characters allowed!", 1, NULL);
}

void	ft_color_help(char *str)
{
	if (str[0] && (str[0] == 'C' || str[0] == 'F')
		&& (str[1] != ' ' && str[1] != '\t'))
		ft_error("Incorrect color input!", 1, NULL);
}

void	ft_get_map_max(t_data *data)
{
	int	i;
	int	j;
	int	max;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (max <= j)
				max = j;
		}
	}
	data->map_x = i;
	data->map_y = max + 1;
}
