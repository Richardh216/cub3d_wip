/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:33:47 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/21 15:47:54 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	skip_leading_spaces(char *str, int pos)
{
	while (str[pos])
	{
		if (str[pos] == ' ')
			pos++;
		else
			return (pos);
	}
	return (pos);
}

char	*ft_extract_color(char *str, int i)
{
	int		j;
	char	*new;

	new = ft_strdup("");
	j = 0;
	while (str[i] && str[i] != '\n')
	{
		i = skip_leading_spaces(str, i);
		if (str[i] != ' ')
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

void	ft_get_color_2(char *top, char *bottom, t_data *data, char *str)
{
	char	**b;
	char	**t;
	int		i;

	if (bottom)
		b = ft_split(str + 1, ',');
	if (top)
		t = ft_split(str + 1, ',');
	if (bottom)
		free(bottom);
	if (top)
		free(top);
	i = -1;
	if (!ft_strncmp(str, "C", 1))
		while (t[++i])
			data->top[i] = ft_atoi(t[i]);
	i = -1;
	if (!ft_strncmp(str, "F", 1))
		while (b[++i])
			data->bottom[i] = ft_atoi(b[i]);
}

void	ft_get_color(t_data *data, char *str)
{
	int		i;
	char	*top;
	char	*bottom;

	top = NULL;
	bottom = NULL;
	i = -1;
	while (str[++i])
	{
		i = skip_leading_spaces(str, i);
		if (!ft_strncmp(str, "C", 1))
		{
			top = ft_extract_color(str, i);
			break ;
		}
		else if (!ft_strncmp(str, "F", 1))
		{
			bottom = ft_extract_color(str, i);
			break ;
		}
	}
	ft_get_color_2(top, bottom, data, str);
}

void	ft_config(t_data *data, char *str)
{
	int	j;
	int	k;
	int	count;
	int	flag;

	j = 0;
	flag = (!ft_strncmp(str, "C ", 2) || !ft_strncmp(str, "F ", 2));
	if (flag)
	{
		k = j;
		count = 0;
		while (str[k])
			if (str[k++] == ',')
				count++;
		if (count != 2)
			ft_error("Invalid RGB format!", 1);
	}
	if (flag)
		ft_get_color(data, str);
	else
		ft_get_path(data, str);
		// printf("PAth\n");
}
