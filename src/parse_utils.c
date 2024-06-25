/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:06:31 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/25 11:22:46 by rhorvath         ###   ########.fr       */
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
	while (data->bottom[++i])
		if (data->bottom[i] < 0 || data->bottom[i] > 255)
			ft_error("Incorrect RGB values!", 1);
	i = -1;
	while (data->top[++i])
		if (data->top[i] < 0 || data->top[i] > 255)
			ft_error("Incorrect RGB values!", 1);
}

void	check_help(char *str, int i)
{
	if (!ft_isdigit(str[i]) && str[i] != ' '
		&& str[i] != '\t' && str[i] != ',')
		ft_error("No characters allowed!", 1);
}
