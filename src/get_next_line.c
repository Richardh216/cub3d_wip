/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:25:44 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/19 12:37:53 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*get_line1(t_lista *list)
{
	int		str_len;
	char	*next_str;

	if (list == NULL)
		return (NULL);
	str_len = len_till_newline(list);
	next_str = malloc(str_len + 1);
	if (next_str == NULL)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}

void	append(t_lista **list, char *buf)
{
	t_lista	*new_node;
	t_lista	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_lista));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buf;
	new_node->next = NULL;
}

void	create_list(t_lista **list, int fd)
{
	int		char_read;
	char	*buf;

	while (!found_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read == 0)
		{
			free(buf);
			return ;
		}
		if (char_read == -1)
		{
			free(buf);
			dealloc(1, list, NULL, NULL);
			*list = NULL;
			return ;
		}
		buf[char_read] = '\0';
		append(list, buf);
	}
}

char	*clean_up_list(t_lista **list)
{
	t_lista	*last_node;
	t_lista	*clean_node;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	clean_node = malloc(sizeof(t_lista));
	if (!clean_node)
		return (free(buf), NULL);
	last_node = find_last_node(*list);
	i = 0;
	k = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		++i;
	while (last_node->str_buf[i] && last_node->str_buf[++i])
		buf[k++] = last_node->str_buf[i];
	buf[k] = '\0';
	clean_node->str_buf = buf;
	clean_node->next = NULL;
	dealloc(0, list, clean_node, buf);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_lista		*list;
	char				*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (list)
		{
			free(list);
		}
		list = NULL;
		return (NULL);
	}
	create_list(&list, fd);
	if (list == NULL)
		return (NULL);
	next_line = get_line1(list);
	clean_up_list(&list);
	return (next_line);
}
