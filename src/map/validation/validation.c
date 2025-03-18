/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:03:37 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/18 17:11:23 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	check_required_textures(t_map_info *map_info)
{
	if (!map_info->no_texture)
	{
		printf("Error:\n Texture Nord (NO) manquante.\n");
		return (0);
	}
	if (!map_info->so_texture)
	{
		printf("Error:\n Texture Sud (SO) manquante.\n");
		return (0);
	}
	if (!map_info->we_texture)
	{
		printf("Error:\n Texture Ouest (WE) manquante.\n");
		return (0);
	}
	if (!map_info->ea_texture)
	{
		printf("Error:\n Texture Est (EA) manquante.\n");
		return (0);
	}
	return (1);
}

int	check_required_elements(t_map_info *map_info)
{
	if (!check_required_textures(map_info))
		return (0);
	if (map_info->floor_color == -1)
	{
		printf("Error:\n Couleur du sol (F) manquante.\n");
		return (0);
	}
	if (map_info->ceiling_color == -1)
	{
		printf("Error:\n Couleur du plafond (C) manquante.\n");
		return (0);
	}
	return (1);
}

void	detect_player(t_map_info *map_info)
{
	int	i;
	int	j;

	i = 0;
	while (map_info->map[i])
	{
		j = 0;
		while (map_info->map[i][j])
		{
			if (map_info->map[i][j] == 'N' || map_info->map[i][j] == 'S'
				|| map_info->map[i][j] == 'E' || map_info->map[i][j] == 'W')
			{
				map_info->player_x = j * 10;
				map_info->player_y = i * 10;
				map_info->player_dir = map_info->map[i][j];
			}
			j++;
		}
		i++;
	}
}

int	is_valid_map_file(char *filename)
{
	int	len;

	len = strlen(filename);
	return (len > 4 && strcmp(filename + len - 4, ".cub") == 0);
}
