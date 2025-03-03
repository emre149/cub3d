/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 04:00:18 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/03 15:51:06 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_glist	*stash = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
	{
		free_stash(stash);
		stash = NULL;
		return (NULL);
	}
	line = NULL;
	read_to_stash(fd, &stash);
	if (stash == NULL)
		return (NULL);
	(stash_to_line(stash, &line), clean(&stash));
	if (line && line[0] == '\0')
	{
		if (stash)
		{
			free_stash(stash);
			stash = NULL;
		}
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_to_stash(int fd, t_glist **stash)
{
	char	*buf;
	int		readed;

	readed = 1;
	while (!newline(*stash) && readed != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return ;
		readed = (int)read(fd, buf, BUFFER_SIZE);
		if ((*stash == NULL && readed == 0) || readed == -1)
		{
			free(buf);
			return ;
		}
		buf[readed] = '\0';
		add(stash, buf, readed);
		free(buf);
	}
}

static void	init_new_node(t_glist **new_node, char *buf, int already_read)
{
	int	i;

	(*new_node)->next = NULL;
	(*new_node)->content = malloc(sizeof(char) * (already_read + 1));
	if (!(*new_node)->content)
		return ;
	i = 0;
	while (buf[i] && i < already_read)
	{
		(*new_node)->content[i] = buf[i];
		i++;
	}
	(*new_node)->content[i] = '\0';
}

void	add(t_glist **stash, char *buf, int already_read)
{
	t_glist	*last_node;
	t_glist	*new_node;

	new_node = malloc(sizeof(t_glist));
	if (!new_node)
		return ;
	init_new_node(&new_node, buf, already_read);
	if (!new_node->content)
	{
		free(new_node);
		return ;
	}
	if (!*stash)
	{
		*stash = new_node;
		return ;
	}
	last_node = ft_glistlast(*stash);
	last_node->next = new_node;
}

void	stash_to_line(t_glist *stash, char **line)
{
	int	i;
	int	j;

	j = 0;
	if (!stash)
		return ;
	line_allocation(line, stash);
	if (!*line)
		return ;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}
