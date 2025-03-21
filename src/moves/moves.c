/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:45:38 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/21 16:57:33 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	move(t_map_info *map_info)
{
	int	key_pressed;

	key_pressed = 0;
	if (map_info->move[X] != 0)
		key_pressed = 1;
	if (map_info->move[Y] != 0)
		key_pressed = 1;
	if (map_info->rot_left || map_info->rot_right)
		key_pressed = 1;
	if (key_pressed == 0)
		return (0);
	return (1);
}

static int	handle_player_rotation(t_map_info *map_info)
{
	int	rotation_moved;
	int	right_moved;

	rotation_moved = 0;
	right_moved = 0;
	if (map_info->rot_left)
		rotation_moved = left_rotate(map_info);
	if (map_info->rot_right)
		right_moved = right_rotate(map_info);
	if (rotation_moved || right_moved)
		return (1);
	return (0);
}

static int	handle_player_movement(t_map_info *map_info)
{
	int	movement_moved;
	int	y_moved;

	movement_moved = 0;
	y_moved = 0;
	if (map_info->move[X] != 0)
		movement_moved = x_move(map_info, map_info->move[X]);
	if (map_info->move[Y] != 0)
		y_moved = y_move(map_info, map_info->move[Y]);
	if (movement_moved || y_moved)
		return (1);
	return (0);
}

int	moves(t_map_info *map_info)
{
	int	moved;
	int	rotation_moved;
	int	movement_moved;

	map_info->moved = move(map_info);
	if (map_info->moved == 0)
		return (1);
	raycasting(map_info);
	movement_moved = handle_player_movement(map_info);
	rotation_moved = handle_player_rotation(map_info);
	moved = 0;
	if (movement_moved || rotation_moved)
		moved = 1;
	map_info->is_walking = (map_info->move[X] != 0 || map_info->move[Y] != 0);
	return (moved);
}
