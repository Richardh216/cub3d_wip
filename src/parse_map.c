/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:13:24 by rhorvath          #+#    #+#             */
/*   Updated: 2024/07/05 12:19:01 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_flood_map(t_data *data, char **map, t_pos pos, int flag)
{
	if (flag && (pos.y < 0 || pos.x < 0 || !map[pos.x] || pos.y
			>= (int)ft_strlen(map[pos.x]) || !map[pos.x][pos.y]))
		path_error(data, "Map not closed properly!", NULL);
	if (pos.y < 0 || pos.x < 0 || !map[pos.x] || pos.y
		>= (int)ft_strlen(map[pos.x]) || !map[pos.x][pos.y])
		return (0);
	if (map[pos.x][pos.y] == '1' || map[pos.x][pos.y] == 'F')
		return (0);
	if (map[pos.x][pos.y] == ' ')
		path_error(data, "Map not closed properly!", NULL);
	if (map[pos.x][pos.y] == '0' || map[pos.x][pos.y] == 'N'
		|| map[pos.x][pos.y] == 'E' || map[pos.x][pos.y] == 'S'
			|| map[pos.x][pos.y] == 'W' || map[pos.x][pos.y] == 'D')
	{
		map[pos.x][pos.y] = 'F';
		ft_flood_map(data, map, (t_pos){pos.x - 1, pos.y}, 1);
		ft_flood_map(data, map, (t_pos){pos.x, pos.y + 1}, 1);
		ft_flood_map(data, map, (t_pos){pos.x + 1, pos.y}, 1);
		ft_flood_map(data, map, (t_pos){pos.x, pos.y - 1}, 1);
	}
	return (0);
}

void	ft_map_cpy(t_data *data)
{
	int		i;
	char	**cpy_map;
	t_pos	pos;

	pos = *data->pos;
	i = 0;
	while (data->map[i])
		i++;
	cpy_map = (char **)malloc(sizeof(char *) * (i + 1));
	if (!cpy_map)
		ft_error("Malloc error!", 1, NULL);
	i = 0;
	while (data->map[i])
	{
		cpy_map[i] = ft_strdup(data->map[i]);
		if (!cpy_map[i])
			ft_error("Malloc error!", 1, NULL);
		i++;
	}
	cpy_map[i] = NULL;
	ft_flood_map(data, cpy_map, (t_pos){pos.x, pos.y}, 0);
	free_mat(cpy_map);
	ft_map_uniform(data);
}

void	ft_check_map(t_data *data, char *str, int ind)
{
	int	i;
	int	j;

	data->map = ft_split(str + ind, '\n');
	free(str);
	if (!data->map)
		ft_error("Malloc error!", 1, NULL);
	ft_get_map_max(data);
	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'E'
				|| data->map[i][j] == 'S' || data->map[i][j] == 'W')
			{
				data->pos->y = j;
				data->pos->x = i;
			}
		}
	}
	if (data->pos->x == -1 || data->pos->y == -1)
		path_error(data, "No starting position found!", NULL);
	ft_map_cpy(data);
}

static int	get_last(char *str, int i, t_data *data)
{
	int	last;

	last = i;
	while (str[last])
		last++;
	while (--last)
	{
		if (str[last] && str[last] != ' ' && str[last] != '\n')
			break ;
	}
	while (i < last)
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != ' '
			&& str[i] != '\n' && str[i] != 'N' && str[i] != 'W'
			&& str[i] != 'S' && str[i] != 'E' && str[i] != 'D')
			path_error(data, "Invalid map!", NULL);
		i++;
	}
	return (last);
}

void	ft_get_map(t_data *data, char *str, int j)
{
	int		ind;
	int		last;

	if (!str)
		ft_error("Map not found!", 1, NULL);
	last = get_last(str, j, data);
	ind = j;
	while (j < last)
	{
		if (str[j] == '\n')
		{
			j++;
			while (j < last && (str[j] == ' ' || str[j] == '\t'))
				j++;
			if (j < last && str[j] == '\n')
				path_error(data, "Newline in map!", str);
		}
		j++;
	}
	ft_check_map(data, str, ind);
}
