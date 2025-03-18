/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:51:32 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/18 17:09:32 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	check_texture_exists(char *texture_path)
{
	int	fd;

	if (!texture_path)
		return (0);
	fd = open(texture_path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	validate_textures(t_map_info *map_info)
{
	if (!check_texture_exists(map_info->no_texture))
		return (0);
	if (!check_texture_exists(map_info->so_texture))
		return (0);
	if (!check_texture_exists(map_info->we_texture))
		return (0);
	if (!check_texture_exists(map_info->ea_texture))
		return (0);
	if (map_info->sprite && !check_texture_exists(map_info->sprite))
		return (0);
	if (map_info->door_text && !check_texture_exists(map_info->door_text))
		return (0);
	return (1);
}

int	check_elements(t_map_info *map_info)
{
	if (!map_info->no_texture || !map_info->so_texture || !map_info->we_texture
		|| !map_info->ea_texture)
	{
		printf("Error:\n Texture manquante\n");
		return (0);
	}
	if (map_info->floor_color == -1 || map_info->ceiling_color == -1)
	{
		printf("Error:\n Couleur manquante\n");
		return (0);
	}
	return (1);
}
