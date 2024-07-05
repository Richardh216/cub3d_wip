/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:41:06 by rhorvath          #+#    #+#             */
/*   Updated: 2024/07/05 12:21:33 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*rspaces(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && (str[i] == '\t' || str[i] == ' '))
		i++;
	while (str[j])
		j++;
	j--;
	while (str[j] && (str[j] == ' ' || str[j] == '\t'))
		j--;
	new = ft_substr(str, i, j - i + 1);
	free(str);
	return (new);
}

char	*ft_extract_path(char *str)
{
	char	*new;
	int		i;

	if (ft_strlen(str) <= 3)
		ft_error("Invalid path!", 1, NULL);
	if (str[2] != ' ' && str[2] != '\t')
		ft_error("Invalid path!", 1, NULL);
	i = 2;
	i = skip_leading_spaces(str, i);
	new = ft_substr(str, i, ft_strlen(str));
	new = rspaces(new);
	return (new);
}

void	ft_get_path(t_data *data, char *str)
{
	char			*path;
	mlx_texture_t	*tex;

	path = ft_extract_path(str);
	if (!path)
		path_error(data, "Malloc failed", NULL);
	tex = mlx_load_png(path);
	if (path)
		free(path);
	if (!tex)
		path_error(data, "Mlx_load_png failed!", NULL);
	if (!ft_strncmp(str, "EA", 2) && !data->tex[2])
		data->tex[2] = tex;
	else if (!ft_strncmp(str, "WE", 2) && !data->tex[3])
		data->tex[3] = tex;
	else if (!ft_strncmp(str, "NO", 2) && !data->tex[0])
		data->tex[0] = tex;
	else if (!ft_strncmp(str, "SO", 2) && !data->tex[1])
		data->tex[1] = tex;
	else
		path_error(data, "Issa problem innit?", NULL);
}

void	ft_map_uniform(t_data *data)
{
	char	**new_map;
	int		i;
	int		len;

	new_map = (char **)malloc(sizeof(char *) * (data->map_x + 1));
	if (!new_map)
		ft_error("Malloc error!", 1, NULL);
	i = 0;
	while (data->map[i])
	{
		len = ft_strlen(data->map[i]);
		new_map[i] = (char *)malloc(sizeof(char) * (data->map_y + 1));
		if (!new_map[i])
			ft_error("Malloc error!", 1, NULL);
		ft_strlcpy(new_map[i], data->map[i], data->map_y + 1);
		ft_memset(new_map[i] + len, ' ', data->map_y - len);
		new_map[i][data->map_y] = '\0';
		i++;
	}
	new_map[i] = NULL;
	free_mat(data->map);
	data->map = new_map;
}
