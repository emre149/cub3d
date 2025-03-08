/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:34:03 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/08 15:54:47 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	process_config_line(t_map_info *map_info, char *line,
		int *map_started)
{
	if (*map_started && !is_map_line(line))
	{
		printf("Error:\n Ligne d'info après la carte: %s\n", line);
		return (0);
	}
	if (ft_strncmp(line, "R ", 2) == 0)
		parse_resolution(map_info, line);
	else if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (!parse_texture(&map_info->no_texture, line, "NO"))
			return (0);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (!parse_texture(&map_info->so_texture, line, "SO"))
			return (0);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (!parse_texture(&map_info->we_texture, line, "WE"))
			return (0);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (!parse_texture(&map_info->ea_texture, line, "EA"))
			return (0);
	}
	else if (ft_strncmp(line, "S ", 2) == 0)
	{
		if (!parse_texture(&map_info->sprite, line, "S"))
			return (0);
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (!parse_color(&map_info->floor_color, line, "F"))
			return (0);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (!parse_color(&map_info->ceiling_color, line, "C"))
			return (0);
	}
	else if (ft_strncmp(line, "DO ", 3) == 0)
	{
		if (!parse_texture(&map_info->door_text, line, "DO"))
			return (0);
	}
	else if (is_map_line(line))
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

int	parse_config(t_map_info *map_info)
{
	int		i;
	int		ret;
	char	*line;
	int		map_started;

	map_info->floor_color = -1;
	map_info->ceiling_color = -1;
	map_info->map_width = SCREEN_WIDTH;
	map_info->map_height = SCREEN_HEIGHT;
	map_started = 0;
	i = 0;
	while (map_info->map[i])
	{
		line = map_info->map[i];
		ret = process_config_line(map_info, line, &map_started);
		if (ret == 0)
			return (0);
		if (ret == 2)
			break ;
		i++;
	}
	parse_map_only(map_info);
	if (!check_required_elements(map_info))
		return (0);
	if (!validate_textures(map_info))
	{
		printf("Error:\n Problème de validation des textures\n");
		return (0);
	}
	if (!validate_map(map_info))
	{
		printf("Error:\n Problème de validation de la carte\n");
		return (0);
	}
	return (1);
}
