/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:41:06 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/25 12:38:30 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_png_len(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_strncmp(str + i, ".png", 4))
			return (i + 2);
	return (i);
}

char	*ft_extract_path(char *str, int i)
{
	int		j;
	char	*tmp;
	char	*new;

	if ((!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2)
			|| !ft_strncmp(str, "WE", 2) || !ft_strncmp(str, "EA", 2))
		&& (str[2] != ' ' && str[2] != '\t'))
		ft_error("NO PATH SPACE!", 1);
	tmp = ft_strdup("");
	j = 0;
	while (str[i] && str[i] != '\n')
	{
		i = skip_leading_spaces(str, i);
		tmp[j++] = str[i++];
	}
	tmp[j] = '\0';
	new = ft_substr(tmp, 2, ft_png_len(tmp));
	free(tmp);
	return (new);
}

void	ft_get_path(t_data *data, char *str)
{
	int				i;
	mlx_texture_t	*tex;
	char			*path;

	i = -1;
	path = NULL;
	while (str[++i])
	{
		if (!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2)
			|| !ft_strncmp(str, "WE", 2) || !ft_strncmp(str, "EA", 2))
		{
			path = ft_extract_path(str, i);
			break ;
		}
	}
	printf("THIS PATH: %s\n", path);
	tex = mlx_load_png(path);
	// if (path)
	// 	free(path);
	// if (!tex)
	// 	ft_error("Mlx_load_png failure", 1);
	// if (!ft_strncmp(str, "EA", 2) && !data->tex[0])
	// {
	// 	data->tex[0] = tex;
	// 	printf("EAST RISE\n");
	// }
	// else if (!ft_strncmp(str, "WE", 2) && !data->tex[1])
	// {
	// 	data->tex[1] = tex;
	// 	printf("WEST RISE\n");
	// }
	// else if (!ft_strncmp(str, "NO", 2) && !data->tex[2])
	// {
	// 	data->tex[2] = tex;
	// 	printf("NORTH RISE\n");
	// }
	// else if (!ft_strncmp(str, "SO", 2) && !data->tex[3])
	// {
	// 	data->tex[3] = tex;
	// 	printf("SOUTH RISE\n");
	// }
	// else
	// 	ft_error("Issa problem innit?", 1);
	(void)data;
}
