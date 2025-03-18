/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:50:11 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/18 17:12:12 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_map_info(t_map_info *map_info)
{
	map_info->floor_color = -1;
	map_info->ceiling_color = -1;
	map_info->map_width = SCREEN_WIDTH;
	map_info->map_height = SCREEN_HEIGHT;
}

static int	validate_config(t_map_info *map_info)
{
	if (!check_elements(map_info))
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

static int	process_map_lines(t_map_info *map_info)
{
	int		i;
	int		ret;
	char	*line;
	int		map_started;

	i = 0;
	map_started = 0;
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
	return (1);
}

int	parse_config(t_map_info *map_info)
{
	init_map_info(map_info);
	if (!process_map_lines(map_info))
		return (0);
	parse_map_only(map_info);
	if (!validate_config(map_info))
		return (0);
	return (1);
}
