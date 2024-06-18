/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:00:21 by rhorvath          #+#    #+#             */
/*   Updated: 2023/04/18 13:19:43 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*result;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	result = ft_calloc((total_len + 1), sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, s1, ft_strlen(s1));
	ft_memcpy(result + ft_strlen(s1), s2, ft_strlen(s2));
	return (result);
}
