/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:33:47 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/20 16:57:12 by rhorvath         ###   ########.fr       */
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

// char *ft_extract_path(char *str, int i)
// {
// 	char	*tmp;

// 	tmp = NULL;
// 	while (str[i] && str[i] != '\n')
// 	{
// 		tmp[j]
// 	}
// }

// void	ft_get_path(t_data *data, char *str)
// {
// 	int	i;

// 	i = -1;
// 	while (str[++i])
// 	{
// 		i = skip_leading_spaces(str, i);
// 		if (!ft_strncmp(str, "NO", 2))
// 			ft_extract_path(str + 2, i);
// 	}
// 	(void)data;
// }

void	ft_get_color(t_data *data, char *str)
{
	int		i;
	char	**top;
	char	**bottom;

	i = -1;
	while (str[++i])
	{
		i = skip_leading_spaces(str, i);
		if (!ft_strncmp(str, "C", 1))
			top = ft_split(str + 2, ',');
		else if (!ft_strncmp(str, "F", 1))
			bottom = ft_split(str + 2, ',');
	}
	i = -1;
	if (!ft_strncmp(str, "C", 1))
		while (top[++i])
			data->top[i] = ft_atoi(top[i]);
	i = -1;
	if (!ft_strncmp(str, "F", 1))
		while (bottom[++i])
			data->bottom[i] = ft_atoi(bottom[i]);
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
		printf("PAth");
		// ft_get_path(data, str);
}
