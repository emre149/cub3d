/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:13:04 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/20 21:06:27 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_ray(t_map_info *map_info, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	map_info->ray_dir[0] = map_info->dir[0] + map_info->plane[0] * camera_x;
	map_info->ray_dir[1] = map_info->dir[1] + map_info->plane[1] * camera_x;
	map_info->map_p[0] = (int)map_info->pos[0];
	map_info->map_p[1] = (int)map_info->pos[1];
	if (map_info->ray_dir[0] == 0)
		map_info->ddist[0] = 1e30;
	else
		map_info->ddist[0] = fabs(1 / map_info->ray_dir[0]);
	if (map_info->ray_dir[1] == 0)
		map_info->ddist[1] = 1e30;
	else
		map_info->ddist[1] = fabs(1 / map_info->ray_dir[1]);
	map_info->hit = 0;
}
