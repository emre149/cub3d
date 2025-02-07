/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:35:43 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/07 15:40:02 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	validate_texture_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(path + len - 4, ".xpm", 4) == 0);
}

static int	check_texture_file(char *path)
{
	int	fd;

	if (!path)
		return (0);
	if (!validate_texture_extension(path))
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static int	check_all_textures_exist(t_map_info *map_info)
{
	if (!map_info->north_texture || !map_info->south_texture
		|| !map_info->west_texture || !map_info->east_texture)
		return (0);
	return (1);
}

int	validate_textures(t_map_info *map_info)
{
	if (!check_all_textures_exist(map_info))
		return (0);
	if (!check_texture_file(map_info->north_texture))
		return (0);
	if (!check_texture_file(map_info->south_texture))
		return (0);
	if (!check_texture_file(map_info->west_texture))
		return (0);
	if (!check_texture_file(map_info->east_texture))
		return (0);
	return (1);
}
