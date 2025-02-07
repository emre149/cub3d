/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:35:29 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/07 15:39:52 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	init_map(t_map_info *map_info)
{
	map_info->map = ft_calloc(1, sizeof(char *));
	if (!map_info->map)
		return (0);
	map_info->map_width = 0;
	map_info->map_height = 0;
	return (1);
}

static int	pad_line(char **line, int target_width)
{
	char	*padded;
	int		i;
	int		len;

	len = ft_strlen(*line);
	padded = malloc(target_width + 1);
	if (!padded)
		return (0);
	i = 0;
	while (i < len)
	{
		padded[i] = (*line)[i];
		i++;
	}
	while (i < target_width)
	{
		padded[i] = ' ';
		i++;
	}
	padded[i] = '\0';
	free(*line);
	*line = padded;
	return (1);
}

static int	add_line_to_map(t_map_info *map_info, char *line)
{
	char	**new_map;
	int		new_size;

	new_size = map_info->map_height + 2;
	new_map = ft_realloc(map_info->map, new_size * sizeof(char *));
	if (!new_map)
		return (0);
	map_info->map = new_map;
	map_info->map[map_info->map_height] = line;
	map_info->map[map_info->map_height + 1] = NULL;
	map_info->map_height++;
	return (1);
}

static int	process_map_line(t_map_info *map_info, char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > map_info->map_width)
		map_info->map_width = len;
	return (add_line_to_map(map_info, line));
}

int	read_map(t_map_info *map_info, int fd)
{
	char *line;
	int i;

	if (!init_map(map_info))
		return (0);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (!process_map_line(map_info, line))
		{
			free(line);
			return (0);
		}
	}
	i = 0;
	while (i < map_info->map_height)
	{
		if (!pad_line(&map_info->map[i], map_info->map_width))
			return (0);
		i++;
	}
	return (1);
}