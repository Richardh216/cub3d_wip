/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:28:10 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/18 14:20:16 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//may need not exiting ft_error

int	ft_error(char *str, int flag)
{
	ft_putstr_fd("cub3d: Error", 2);
	if (str)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
	}
	ft_putchar_fd('\n', 2);
	exit(flag);
}
