/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:05:47 by marvin            #+#    #+#             */
/*   Updated: 2025/02/27 16:05:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int right_rotate(t_map_info *map_info)
{
    double old_dir_x;
    double old_plane_x;

    old_dir_x = map_info->dir[X];
    old_plane_x = map_info->plane[X];
    map_info->dir[X] = map_info->dir[X] * cos(R_SPEED) - map_info->dir[Y] * sin(R_SPEED);
    map_info->dir[Y] = old_dir_x * sin(R_SPEED) + map_info->dir[Y] * cos(R_SPEED);
    map_info->plane[X] = map_info->plane[X] * cos(R_SPEED) - map_info->plane[Y] * sin(R_SPEED);
    map_info->plane[Y] = old_plane_x * sin(R_SPEED) + map_info->plane[Y] * cos(R_SPEED);
    return (1);
}

int left_rotate(t_map_info *map_info)
{
    double old_dir_x;
    double old_plane_x;

    old_dir_x = map_info->dir[X];
    old_plane_x = map_info->plane[X];
    map_info->dir[X] = map_info->dir[X] * cos(-R_SPEED) - map_info->dir[Y] * sin(-R_SPEED);
    map_info->dir[Y] = old_dir_x * sin(-R_SPEED) + map_info->dir[Y] * cos(-R_SPEED);
    map_info->plane[X] = map_info->plane[X] * cos(-R_SPEED) - map_info->plane[Y] * sin(-R_SPEED);
    map_info->plane[Y] = old_plane_x * sin(-R_SPEED) + map_info->plane[Y] * cos(-R_SPEED);
    return (1);
}

int moves(t_map_info *map_info)
{
    map_info->moved += move(map_info);
    if (map_info->moved == 0)
        return (1);
    raycasting(map_info);
    return (0);
}
