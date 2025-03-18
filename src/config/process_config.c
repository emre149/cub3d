/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:24:06 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/18 14:29:31 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	process_texture_line_north_south(t_map_info *map_info, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (!parse_texture(&map_info->no_texture, line, "NO"))
			return (0);
		return (1);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (!parse_texture(&map_info->so_texture, line, "SO"))
			return (0);
		return (1);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (!parse_texture(&map_info->we_texture, line, "WE"))
			return (0);
		return (1);
	}
	return (2);
}

int	process_texture_line(t_map_info *map_info, char *line)
{
	int	ret;

	ret = process_texture_line_north_south(map_info, line);
	if (ret != 2)
		return (ret);
	if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (!parse_texture(&map_info->ea_texture, line, "EA"))
			return (0);
	}
	else if (ft_strncmp(line, "S ", 2) == 0)
	{
		if (!parse_texture(&map_info->sprite, line, "S"))
			return (0);
	}
	else if (ft_strncmp(line, "DO ", 3) == 0)
	{
		if (!parse_texture(&map_info->door_text, line, "DO"))
			return (0);
	}
	else
		return (2);
	return (1);
}

int	process_color_line(t_map_info *map_info, char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (!parse_color(&map_info->floor_color, line, "F"))
			return (0);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (!parse_color(&map_info->ceiling_color, line, "C"))
			return (0);
	}
	else
		return (2);
	return (1);
}

int	process_map_line(char *line, int *map_started)
{
	if (is_map_line(line))
	{
		*map_started = 1;
		return (2);
	}
	else if (line[0] != '\0')
	{
		printf("Error:\n Ligne non reconnue: %s\n", line);
		return (0);
	}
	return (1);
}

int	process_config_line(t_map_info *map_info, char *line, int *map_started)
{
	int	ret;

	if (*map_started && !is_map_line(line))
	{
		printf("Error:\n Ligne d'info après la carte: %s\n", line);
		return (0);
	}
	if (ft_strncmp(line, "R ", 2) == 0)
	{
		parse_resolution(map_info, line);
		return (1);
	}
	ret = process_texture_line(map_info, line);
	if (ret != 2)
		return (ret);
	ret = process_color_line(map_info, line);
	if (ret != 2)
		return (ret);
	return (process_map_line(line, map_started));
}
