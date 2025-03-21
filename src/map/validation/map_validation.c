/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:00:11 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/21 17:33:24 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_map_only(t_map_info *map_info)
{
	int		start;
	int		end;
	char	**new_map;

	start = -1;
	end = -1;
	if (!map_info->map)
		return ;
	if (!get_map_bounds(map_info->map, &start, &end))
		return ;
	new_map = duplicate_map_lines(map_info->map, start, end);
	if (!new_map)
		return ;
	free_map(map_info->map);
	map_info->map = new_map;
}

void	set_player_position(t_map_info *map_info)
{
	map_info->dir_x = map_info->dir[X];
	map_info->dir_y = map_info->dir[Y];
	map_info->plane_x = map_info->plane[X];
	map_info->plane_y = map_info->plane[Y];
	map_info->pos[X] = (double)map_info->player_x / 10;
	map_info->pos[Y] = (double)map_info->player_y / 10;
}

int	validate_map(t_map_info *map_info)
{
	if (!map_info->map)
	{
		printf("Error:\n Aucune carte à valider\n");
		return (0);
	}
	if (!check_valid_chars(map_info->map))
		return (0);
	normalize_map(map_info->map, map_info);
	if (!check_map_closed(map_info->map))
	{
		restore_player(map_info);
		return (0);
	}
	restore_player(map_info);
	init_player_direction(map_info);
	return (1);
}

int	close_return(int fd)
{
	close(fd);
	return (0);
}
