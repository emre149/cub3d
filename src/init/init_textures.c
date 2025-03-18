/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:00:50 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/18 16:02:06 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	*stock_tmp(t_map_info *map_info, char *path)
{
	t_img	tmp;
	int		*array;
	int		x;
	int		y;

	xpm_to_img(map_info, &tmp, path);
	array = ft_calloc(1, sizeof(int) * (IMG_SIZE * IMG_SIZE));
	if (!array)
		error_exit(map_info, "Failed to allocate memory for texture");
	y = -1;
	while (++y < IMG_SIZE)
	{
		x = -1;
		while (++x < IMG_SIZE)
			array[y * IMG_SIZE + x] = tmp.addr[y * (tmp.line_length / 4) + x];
	}
	mlx_destroy_image(map_info->mlx, tmp.img_mlx);
	return (array);
}

static int	check_for_doors(t_map_info *map_info)
{
	int	i;
	int	j;
	int	has_doors;

	has_doors = 0;
	i = 0;
	while (map_info->map[i])
	{
		j = 0;
		while (map_info->map[i][j])
		{
			if (map_info->map[i][j] == DOOR_CLOSE
				|| map_info->map[i][j] == DOOR_OPEN)
			{
				has_doors = 1;
				break ;
			}
			j++;
		}
		if (has_doors)
			break ;
		i++;
	}
	return (has_doors);
}

static void	validate_door_textures(t_map_info *map_info, int has_doors)
{
	if (has_doors && !map_info->door_text)
		error_exit(map_info,
			"Des portes sont présentes dans la carte mais aucune texture de \
            porte (DO) n'est définie");
	if (!has_doors && map_info->door_text)
		error_exit(map_info,
			"Une texture de porte (DO) est définie mais aucune porte n'est \
            présente dans la carte");
	if (map_info->door_text)
		map_info->assets[DOOR] = stock_tmp(map_info, map_info->door_text);
}

void	init_textures(t_map_info *map_info)
{
	int	has_doors;

	map_info->assets = ft_calloc(6, sizeof(int *));
	if (!map_info->assets)
		error_exit(map_info, "Failed to allocate memory for textures array");
	printf("Loading textures...\n");
	map_info->assets[NO] = stock_tmp(map_info, map_info->no_texture);
	map_info->assets[SO] = stock_tmp(map_info, map_info->so_texture);
	map_info->assets[WE] = stock_tmp(map_info, map_info->we_texture);
	map_info->assets[EA] = stock_tmp(map_info, map_info->ea_texture);
	has_doors = check_for_doors(map_info);
	validate_door_textures(map_info, has_doors);
	printf("Textures loaded\n");
}
