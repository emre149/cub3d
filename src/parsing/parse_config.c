/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:34:03 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/01 17:32:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	parse_resolution(t_map_info *map_info, char *line)
{
	int	i;

	i = 1;
	while (line[i] == ' ')
		i++;
	map_info->map_width = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ')
		i++;
	map_info->map_height = ft_atoi(&line[i]);
}

void	parse_texture(char **texture, char *line)
{
	if (*texture)
		free(*texture);
	*texture = ft_strdup(line);
	if (!*texture)
		error_exit(NULL, "Failed to allocate memory for texture");
}

void	parse_color(int *color, char *line)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 1;
	while (line[i] == ' ')
		i++;
	r = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ' || line[i] == ',')
		i++;
	g = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ' || line[i] == ',')
		i++;
	b = ft_atoi(&line[i]);
	*color = (r << 16) | (g << 8) | b;
}

static int	process_config_line(t_map_info *map_info, char *line)
{
	if (strncmp(line, "R ", 2) == 0)
		parse_resolution(map_info, line);
	else if (strncmp(line, "NO ", 3) == 0)
		parse_texture(&map_info->no_texture, line);
	else if (strncmp(line, "SO ", 3) == 0)
		parse_texture(&map_info->so_texture, line);
	else if (strncmp(line, "WE ", 3) == 0)
		parse_texture(&map_info->we_texture, line);
	else if (strncmp(line, "EA ", 3) == 0)
		parse_texture(&map_info->ea_texture, line);
	else if (strncmp(line, "S ", 2) == 0)
		parse_texture(&map_info->sprite, line);
	else if (strncmp(line, "F ", 2) == 0)
		parse_color(&map_info->floor_color, line);
	else if (strncmp(line, "C ", 2) == 0)
		parse_color(&map_info->ceiling_color, line);
	else if (is_map_line(line))
	{
		parse_map_only(map_info);
		
		return (2);
	}
	return (1);
}

int	parse_config(t_map_info *map_info)
{
	int		i;
	int		ret;
	char	*line;

	i = 0;
	while (map_info->map[i])
	{
		line = map_info->map[i];
		ret = process_config_line(map_info, line);
		if (ret == 2)
			break ;
		i++;
	}
	return (1);
}
