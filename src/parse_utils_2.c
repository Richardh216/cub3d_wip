/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:41:06 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/24 15:11:43 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*ft_extract_path(char *str, int i)
{
	int		j;
	char	*tmp;
	char	*new;

	tmp = ft_strdup("");
	j = 0;
	while (str[i] && str[i] != '\n')
	{
		i = skip_leading_spaces(str, i);
		tmp[j++] = str[i++];
	}
	tmp[j] = '\0';
	new = ft_substr(tmp, 2, ft_strlen(tmp));
	free(tmp);
	// printf("THIS P: %s\n", new);
	return (new);
}

void	ft_get_path(t_data *data, char *str)
{
	int				i;
	// mlx_texture_t	*tex;
	char			*path;

	i = -1;
	path = NULL;
	while (str[++i])
	{
		i = skip_leading_spaces(str, i);
		if (!ft_strncmp(str, "NO", 2))
		{
			path = ft_extract_path(str, i);
			break ;
		}
		else if (!ft_strncmp(str, "SO", 2))
		{
			path = ft_extract_path(str, i);
			break ;
		}
		else if (!ft_strncmp(str, "WE", 2))
		{
			path = ft_extract_path(str, i);
			break ;
		}
		else if (!ft_strncmp(str, "EA", 2))
		{
			path = ft_extract_path(str, i);
			break ;
		}
	}
	printf("THIS PATH: %s\n", path);
	// tex = mlx_load_png(path);
	// if (path)
	// 	free(path);
	(void)data;
}
