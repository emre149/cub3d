/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:45:17 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/25 17:55:11 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	free_asset(t_map_info *map_info)
{
	int	i;

	if (!map_info->assets)
		return ;
	i = 0;
	while (i < 5)
	{
		if (map_info->assets[i])
			free(map_info->assets[i]);
		i++;
	}
	free(map_info->assets);
}

void	free_all(t_map_info *map_info)
{
	if (map_info->no_texture)
		free(map_info->no_texture);
	if (map_info->so_texture)
		free(map_info->so_texture);
	if (map_info->we_texture)
		free(map_info->we_texture);
	if (map_info->ea_texture)
		free(map_info->ea_texture);
	if (map_info->sprite)
		free(map_info->sprite);
	if (map_info->door_text)
		free(map_info->door_text);
	if (map_info->map)
		free_map(map_info->map);
	if (map_info->assets)
		free_asset(map_info);
	if (map_info->img)
		free(map_info->img);
	if (map_info->mlx && map_info->win)
	{
		mlx_destroy_window(map_info->mlx, map_info->win);
		mlx_destroy_display(map_info->mlx);
		free(map_info->mlx);
	}
}

void	error_exit(t_map_info *map_info, char *message)
{
	printf("Error:\n %s\n", message);
	free_all(map_info);
	exit(1);
}
