/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:20:41 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/18 12:22:26 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	right_rotate(t_map_info *map_info)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = map_info->dir[X];
	old_plane_x = map_info->plane[X];
	map_info->dir[X] = map_info->dir[X] * cos(R_SPEED) - map_info->dir[Y]
		* sin(R_SPEED);
	map_info->dir[Y] = old_dir_x * sin(R_SPEED) + map_info->dir[Y]
		* cos(R_SPEED);
	map_info->plane[X] = map_info->plane[X] * cos(R_SPEED) - map_info->plane[Y]
		* sin(R_SPEED);
	map_info->plane[Y] = old_plane_x * sin(R_SPEED) + map_info->plane[Y]
		* cos(R_SPEED);
	map_info->dir_x = map_info->dir[X];
	map_info->dir_y = map_info->dir[Y];
	map_info->plane_x = map_info->plane[X];
	map_info->plane_y = map_info->plane[Y];
	return (1);
}

int	left_rotate(t_map_info *map_info)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = map_info->dir[X];
	old_plane_x = map_info->plane[X];
	map_info->dir[X] = map_info->dir[X] * cos(-R_SPEED) - map_info->dir[Y]
		* sin(-R_SPEED);
	map_info->dir[Y] = old_dir_x * sin(-R_SPEED) + map_info->dir[Y]
		* cos(-R_SPEED);
	map_info->plane[X] = map_info->plane[X] * cos(-R_SPEED) - map_info->plane[Y]
		* sin(-R_SPEED);
	map_info->plane[Y] = old_plane_x * sin(-R_SPEED) + map_info->plane[Y]
		* cos(-R_SPEED);
	map_info->dir_x = map_info->dir[X];
	map_info->dir_y = map_info->dir[Y];
	map_info->plane_x = map_info->plane[X];
	map_info->plane_y = map_info->plane[Y];
	return (1);
}
