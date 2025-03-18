/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:02:34 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/18 13:02:39 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	normalize_map(char **map, t_map_info *map_info)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				map_info->player_dir = map[i][j];
				map_info->player_x = j * 10;
				map_info->player_y = i * 10;
				map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

void	restore_player(t_map_info *map_info)
{
	int	i;
	int	j;

	i = map_info->player_y / 10;
	j = map_info->player_x / 10;
	if (i >= 0 && j >= 0 && map_info->map[i]
		&& j < (int)ft_strlen(map_info->map[i]))
		map_info->map[i][j] = map_info->player_dir;
}

void	set_player_ns_direction(t_map_info *map_info)
{
	if (map_info->player_dir == 'N')
	{
		map_info->dir[X] = 0;
		map_info->dir[Y] = -1;
		map_info->plane[X] = 0.66;
		map_info->plane[Y] = 0;
	}
	else if (map_info->player_dir == 'S')
	{
		map_info->dir[X] = 0;
		map_info->dir[Y] = 1;
		map_info->plane[X] = -0.66;
		map_info->plane[Y] = 0;
	}
}

void	set_player_ew_direction(t_map_info *map_info)
{
	if (map_info->player_dir == 'E')
	{
		map_info->dir[X] = 1;
		map_info->dir[Y] = 0;
		map_info->plane[X] = 0;
		map_info->plane[Y] = 0.66;
	}
	else if (map_info->player_dir == 'W')
	{
		map_info->dir[X] = -1;
		map_info->dir[Y] = 0;
		map_info->plane[X] = 0;
		map_info->plane[Y] = -0.66;
	}
}

void	init_player_direction(t_map_info *map_info)
{
	set_player_ns_direction(map_info);
	set_player_ew_direction(map_info);
	map_info->dir_x = map_info->dir[X];
	map_info->dir_y = map_info->dir[Y];
	map_info->plane_x = map_info->plane[X];
	map_info->plane_y = map_info->plane[Y];
	map_info->pos[X] = (double)map_info->player_x / 10;
	map_info->pos[Y] = (double)map_info->player_y / 10;
}
