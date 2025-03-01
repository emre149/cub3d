/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:03:37 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/28 11:29:06 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_required_elements(t_map_info *map_info)
{
	if (!map_info->no_texture)
	{
		write(2, "Error: Texture Nord (NO) manquante.\n", 37);
		return (0);
	}
	if (!map_info->so_texture)
	{
		write(2, "Error: Texture Sud (SO) manquante.\n", 36);
		return (0);
	}
	if (!map_info->we_texture)
	{
		write(2, "Error: Texture Ouest (WE) manquante.\n", 38);
		return (0);
	}
	if (!map_info->ea_texture)
	{
		write(2, "Error: Texture Est (EA) manquante.\n", 36);
		return (0);
	}
	if (map_info->floor_color == -1)
	{
		write(2, "Error: Couleur du sol (F) manquante.\n", 38);
		return (0);
	}
	if (map_info->ceiling_color == -1)
	{
		write(2, "Error: Couleur du plafond (C) manquante.\n", 41);
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

int	validate_textures(t_map_info *map_info)
{
	if (!map_info->no_texture || !is_valid_texture_file(map_info->no_texture))
		return (0);
	if (!map_info->so_texture || !is_valid_texture_file(map_info->so_texture))
		return (0);
	if (!map_info->we_texture || !is_valid_texture_file(map_info->we_texture))
		return (0);
	if (!map_info->ea_texture || !is_valid_texture_file(map_info->ea_texture))
		return (0);
	return (1);
}

int	is_valid_map_file(char *filename)
{
	int	len;

	len = strlen(filename);
	return (len > 4 && strcmp(filename + len - 4, ".cub") == 0);
}
