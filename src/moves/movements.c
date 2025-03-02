/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:16:29 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/02 16:26:06 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	can_move(t_map_info *map_info, double x, double y)
{
	if (x < 0.25 || x >= map_info->map_width / 10 - 0.25)
		return (0);
	if (y < 0.25 || y >= map_info->map_height / 10 - 0.25)
		return (0);
	
	if (map_info->map[(int)(y)][(int)(x)] == '1')
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

int	move(t_map_info *map_info)
{
	int	m;

	m = 0;
	
	if (map_info->move[Y] == 1)
		m += y_move(map_info, 1);
	if (map_info->move[Y] == -1)
		m += y_move(map_info, -1);
	
	if (map_info->move[X] == 1)
		m += x_move(map_info, 1);
	if (map_info->move[X] == -1)
		m += x_move(map_info, -1);
	
	if (map_info->rot_left < 0)
		m += left_rotate(map_info);
	if (map_info->rot_right > 0)
		m += right_rotate(map_info);
	
	return (m);
}

int	moves(t_map_info *map_info)
{
	map_info->moved = move(map_info);
	
	if (map_info->moved == 0)
		return (1);
	
	raycasting(map_info);
	return (0);
}
