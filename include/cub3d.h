/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:26:46 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/18 14:31:59 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "../libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*tex[4];
	char			**map;
}	t_data;

//parse
void	ft_parse(t_data *data, char **argv);

//Errors
int		ft_error(char *str, int flag);

#endif