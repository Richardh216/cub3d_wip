/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:33:47 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/27 15:25:25 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	ft_check_color(char *str)
{
	int	i;
	int	count;
	int	flag;

	i = 0;
	count = 0;
	flag = 0;
	if (str[0] && (str[0] == 'C' || str[0] == 'F')
		&& (str[1] != ' ' && str[1] != '\t'))
		ft_error("NO SPACE", 1, str);
	while (str[++i])
	{
		check_help(str, i);
		if (ft_isdigit(str[i]))
		{
			count += 1;
			flag = 0;
			while (str[i] && ft_isdigit(str[i]))
				i++;
			i--;
		}
		if (str[i] == ',')
			flag = 1;
	}
	if (flag || count != 3)
		ft_error("Incorrect color input!", 1, str);
}

void	ft_get_color(t_data *data, char *str)
{
	int		i;
	char	*top;
	char	*bottom;

	top = NULL;
	bottom = NULL;
	i = -1;
	ft_check_color(str);
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
	int	i;
	int	k;
	int	count;
	int	flag;

	i = 0;
	flag = (!ft_strncmp(str, "C", 1) || !ft_strncmp(str, "F", 1));
	if (flag)
	{
		k = i;
		count = 0;
		while (str[k])
			if (str[k++] == ',')
				count++;
		if (count != 2)
			ft_error("Invalid RGB format!", 1, str);
	}
	if (flag && count == 2)
		ft_get_color(data, str);
	else
		ft_get_path(data, str);
}
