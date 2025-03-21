/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:16:29 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/21 16:45:50 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	can_move(t_map_info *map_info, double x, double y)
{
	if (x < 0.25 || x >= map_info->map_width / 10 - 0.25)
		return (0);
	if (y < 0.25 || y >= map_info->map_height / 10 - 0.25)
		return (0);
	if (map_info->map[(int)(y)][(int)(x)] == '1'
		|| map_info->map[(int)(y)][(int)(x)] == DOOR_CLOSE)
		return (0);
	return (1);
}

int	y_move(t_map_info *map_info, int down_up)
{
	double	new_y;
	double	new_x;

	new_y = 0;
	new_x = 0;
	if (down_up == 1)
	{
		new_y = map_info->pos[Y] + map_info->dir[Y] * P_SPEED;
		new_x = map_info->pos[X] + map_info->dir[X] * P_SPEED;
	}
	else if (down_up == -1)
	{
		new_y = map_info->pos[Y] - map_info->dir[Y] * P_SPEED;
		new_x = map_info->pos[X] - map_info->dir[X] * P_SPEED;
	}
	if (!can_move(map_info, new_x, new_y))
		return (0);
	map_info->pos[Y] = new_y;
	map_info->pos[X] = new_x;
	return (1);
}

int	x_move(t_map_info *map_info, int left_right)
{
	double	new_y;
	double	new_x;

	new_y = 0;
	new_x = 0;
	if (left_right == 1)
	{
		new_y = map_info->pos[Y] + map_info->dir[X] * P_SPEED;
		new_x = map_info->pos[X] - map_info->dir[Y] * P_SPEED;
	}
	else if (left_right == -1)
	{
		new_y = map_info->pos[Y] - map_info->dir[X] * P_SPEED;
		new_x = map_info->pos[X] + map_info->dir[Y] * P_SPEED;
	}
	if (!can_move(map_info, new_x, new_y))
		return (0);
	map_info->pos[Y] = new_y;
	map_info->pos[X] = new_x;
	return (1);
}
