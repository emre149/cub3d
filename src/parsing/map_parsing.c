/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:34:40 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/07 16:40:02 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static char	*parse_texture_path(char *line)
{
	char	*path;

	while (*line && ft_isspace(*line))
		line++;
	path = ft_strdup(line);
	if (!path)
		return (NULL);
	while (*path && !ft_isspace(path[ft_strlen(path) - 1]))
		path[ft_strlen(path) - 1] = '\0';
	return (path);
}

static int	init_parsing(char *file_path, int *fd, t_map_info *map_info)
{
	*fd = open(file_path, O_RDONLY);
	if (*fd < 0)
		return (0);
	ft_memset(map_info, 0, sizeof(t_map_info));
	map_info->floor_color = -1;
	map_info->ceiling_color = -1;
	return (1);
}

static int	check_parsing_complete(t_map_info *map_info)
{
	return (map_info->north_texture && map_info->south_texture
		&& map_info->west_texture && map_info->east_texture
		&& map_info->floor_color != -1 && map_info->ceiling_color != -1);
}

static int	parse_line_element(char *line, t_map_info *map_info)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		map_info->north_texture = parse_texture_path(line + 2);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		map_info->south_texture = parse_texture_path(line + 2);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		map_info->west_texture = parse_texture_path(line + 2);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		map_info->east_texture = parse_texture_path(line + 2);
	else if (ft_strncmp(line, "F ", 2) == 0)
		map_info->floor_color = parse_color(line + 1);
	else if (ft_strncmp(line, "C ", 2) == 0)
		map_info->ceiling_color = parse_color(line + 1);
	else if (!ft_isspace_str(line))
		return (0);
	return (1);
}

int	parse_map_file(t_map_info *map_info, char *file_path)
{
	int		fd;
	char	*line;

	if (!init_parsing(file_path, &fd, map_info))
		return (0);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (!parse_line_element(line, map_info))
		{
			if (!check_parsing_complete(map_info))
			{
				free(line);
				close(fd);
				return (0);
			}
			free(line);
			break ;
		}
		free(line);
	}
	if (!read_map(map_info, fd))
		return (0);
	close(fd);
	return (validate_textures(map_info) && valid_map(map_info));
}
