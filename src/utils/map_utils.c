/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:45:17 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/27 15:14:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void free_tex(t_map_info *map_info)
{
	if (map_info->text)
	{
		if (map_info->text[NO])
			free(map_info->text[NO]);
		if (map_info->text[SO])
			free(map_info->text[SO]);
		if (map_info->text[WE])
			free(map_info->text[WE]);
		if (map_info->text[EA])
			free(map_info->text[EA]);
	}
	free(map_info->text);
}

void free_game(t_map_info *map_info)
{
	if (map_info->no_texture)
		free(map_info->no_texture);
	if (map_info->so_texture)
		free(map_info->so_texture);
	if (map_info->we_texture)
		free(map_info->we_texture);
		
}

void free_all(t_map_info *map_info)
{
	if (map_info->map)
		free_map(map_info->map);
	free_tex(map_info);
	free_game(map_info);
	if (map_info->win)
		mlx_destroy_window(map_info->mlx, map_info->win);
	if (map_info->mlx)
		(free(map_info->mlx), mlx_destroy_display(map_info->mlx));
}
